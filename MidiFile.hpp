#ifndef MidiFileHPP
#define MidiFileHPP

#include <Midi/MidiFile.h>

// sequence

Midi::Sequence::Sequence()
   : ticksPer16(1)
   , uSecsPerQuarter(500000) // 120 bpm
   , trackList()
{
}

Midi::Sequence::Info Midi::Sequence::compileInfo() const
{
   Info info;

   info.bpm = 60000000 / uSecsPerQuarter;

   for (const Track& track : trackList)
   {
      if (info.maxTick < track.maxTick)
         info.maxTick = track.maxTick;
   }

   info.barCounter = info.maxTick / (16 * ticksPer16);

   const float beatCounter = 4 * info.barCounter;
   const float beatsPerSecond = static_cast<float>(info.bpm) / 60.0;
   const uint64_t totalSeconds = static_cast<uint64_t>(beatCounter / beatsPerSecond);
   info.seconds = totalSeconds % 60;
   info.minutes = (totalSeconds - info.seconds) / 60;

   return info;
}

const Midi::Sequence::Track::List& Midi::Sequence::getTrackList() const
{
   return trackList;
}

uint64_t Midi::Sequence::compileBarCounter(uint64_t trackIndex) const
{
   const Track& track = trackList.at(trackIndex);
   const uint64_t barCounter = track.maxTick / (16 * ticksPer16);

   return barCounter;
}

TimeCode::Duration Midi::Sequence::fromTick(const Tick& tick)
{
   TimeCode::Duration duration = tick / ticksPer16;
   return duration;
}

Midi::Sequence::Tick Midi::Sequence::toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat)
{
   const float fDuration = static_cast<float>(duration) + precentageToNextBeat;
   const float fTicks = fDuration * ticksPer16;
   const Tick tick = static_cast<Tick>(fTicks);

   return tick;
}

// file reader

Midi::File::Reader::Reader(const Bytes& content)
   : Sequence()
{
   Chunk::List chunkList;
   uint64_t cursor = 0;

   auto subBytes = [&](const uint64_t length)
   {
      const Bytes subData(content.begin() + cursor, content.begin() + cursor + length);
      cursor += length;
      return subData;
   };

   const size_t maxCursor = content.size();
   while (cursor < maxCursor)
   {
      Chunk chunk;

      const Bytes id = subBytes(4);
      chunk.id = std::string(id.begin(), id.end());

      const Bytes lenData = subBytes(4);
      const uint64_t val1 = 256 * 256 * 256 * lenData.at(0);
      const uint64_t val2 = 256 * 256 * lenData.at(1);
      const uint64_t val3 = 256 * lenData.at(2);
      const uint64_t val4 = lenData.at(3);
      const uint64_t length = val1 + val2 + val3 + val4;

      chunk.data = subBytes(length);
      chunkList.push_back(chunk);
   }

   readHeader(chunkList.at(0));
   if (0 == ticksPer16)
      return;

   const size_t maxIndex = chunkList.size();
   for (size_t index = 1; index < maxIndex; index++)
   {
      if (verbose)
         std::cout << "**** track #" << index << std::endl;
      const Chunk& trackChunk = chunkList.at(index);
      readTrack(trackChunk);
   }
}

void Midi::File::Reader::readHeader(const Chunk& headerChunk)
{
   if ("MThd" != headerChunk.id || 6 != headerChunk.data.size())
      return;

   // format 0 & 1
   // no of tracks 2 & 3
   const uint8_t div1 = headerChunk.data.at(4);
   const uint8_t div2 = headerChunk.data.at(5);

   const bool isSMPTE = hasFirstBit(div1);
   if (isSMPTE)
   {
      // TODO
      assert(false);
   }
   else
   {
      const uint16_t ticksPerQuarter = removeFirstBit(div1) * 256 + div2;
      ticksPer16 = ticksPerQuarter / 4;
   }
}

void Midi::File::Reader::readTrack(const Chunk& trackChunk)
{
   if ("MTrk" != trackChunk.id)
      return;

   const uint64_t maxCursor = trackChunk.data.size();
   if (verbose)
      std::cout << __FUNCTION__ << " max " << maxCursor << std::endl;

   Track track;
   Tick fileTick = 0;
   uint64_t cursor = 0;

   Tick lastNoteOnTick = 0;
   Tick lastNoteOffTick = 0;
   while (cursor < maxCursor)
   {
      const Tick tickDiff = variableLength(trackChunk.data, cursor);
      fileTick += tickDiff;

      if (cursor >= maxCursor)
         break;

      const uint8_t marker = trackChunk.data.at(cursor);

      if (verbose)
         std::cout << " @ " << cursor << std::hex << " (Ox" << cursor + 14 + 10 << "), event 0x" << (uint16_t)marker << std::dec << std::endl;

      if (isEvent(marker, Event::Meta))
      {
         cursor += 1; // marker already read
         MetaEvent me = readMetaEventAndAdvanceCursor(trackChunk.data, cursor, &track);

         if (verbose)
            std::cout << "meta event 0x" << std::hex << (uint16_t)me << std::dec << std::endl;

         if (MetaEvent::EndOfTrack == me)
            break;
      }
      else
      {
         if (verbose)
         {
            const TimeCode::Duration timeCode = fromTick(fileTick);
            const std::string timeText = ::TimeCode(timeCode).text();

            std::cout << "event [" << timeText << "]" << std::endl;
         }

         if (isEvent(marker, Event::NoteOn))
            lastNoteOnTick = fileTick;
         else if (isEvent(marker, Event::NoteOff))
            lastNoteOffTick = fileTick;

         const uint8_t length = compileMidiEventLength(marker);
         if (0 == length) // error
         {
            if (verbose)
               std::cout << "----> UNKOWN EVENT" << std::endl;
            break;
         }

         const Bytes message(trackChunk.data.cbegin() + cursor, trackChunk.data.cbegin() + cursor + length);
         track.messageMap[fileTick].push_back(message);

         cursor += length;
      }
   }

   if (0 != track.messageMap.size())
   {
      uint64_t maxTick = fileTick;
      if (0 != lastNoteOffTick && lastNoteOnTick < lastNoteOffTick)
         maxTick = lastNoteOffTick;

      track.maxTick = maxTick;
      trackList.push_back(track);
   }
}

Midi::MetaEvent Midi::File::Reader::readMetaEventAndAdvanceCursor(const Bytes& trackChunkData, uint64_t& cursor, Track* track)
{
   // clang-format off
   static const std::map<uint8_t, uint8_t> messageStaticLengthMap =
      {
         {(uint8_t)MetaEvent::ChannelPrefix, 2},
         {(uint8_t)MetaEvent::SMPTEOffset, 6},
         {(uint8_t)MetaEvent::TimeSignature, 5},
         {(uint8_t)MetaEvent::KeySignature, 3}
      };
   static const std::vector<uint8_t> messageVariableMarkerList =
      {
         (uint8_t)MetaEvent::Text,
         (uint8_t)MetaEvent::Copyright,
         (uint8_t)MetaEvent::TrackName,
         (uint8_t)MetaEvent::InstrumentName,
         (uint8_t)MetaEvent::Lyric,
         (uint8_t)MetaEvent::Marker,
         (uint8_t)MetaEvent::CuePoint,
         (uint8_t)MetaEvent::MidiPort
      };
   // clang-format on

   const uint8_t subMarker = trackChunkData.at(cursor);
   cursor += 1;

   auto subBytes = [&](const uint64_t length)
   {
      const Bytes subData(trackChunkData.begin() + cursor, trackChunkData.begin() + cursor + length);
      cursor += length;
      return subData;
   };

   auto isMetaEvent = [&](const MetaEvent mask)
   {
      return (mask == (mask & subMarker));
   };

   if (messageStaticLengthMap.find(subMarker) != messageStaticLengthMap.end())
   {
      cursor += messageStaticLengthMap.at(subMarker);
      return static_cast<MetaEvent>(subMarker);
   }
   else if (std::find(messageVariableMarkerList.begin(), messageVariableMarkerList.end(), subMarker) != messageVariableMarkerList.end())
   {
      const uint64_t length = variableLength(trackChunkData, cursor);
      const Bytes text = subBytes(length);

      if (verbose)
         std::cout << std::string(text.cbegin(), text.cend()) << std::endl;

      if (MetaEvent::TrackName == (MetaEvent)subMarker && track)
         track->name = std::string(text.begin(), text.end());

      return static_cast<MetaEvent>(subMarker);
   }
   else if (isMetaEvent(MetaEvent::EndOfTrack))
   {
      const Bytes check = subBytes(1);
      (void)check;

      return MetaEvent::EndOfTrack;
   }
   else if (isMetaEvent(MetaEvent::Tempo))
   {
      const Bytes check = subBytes(1);
      (void)check;

      const Bytes lenData = subBytes(3);
      const uint64_t val2 = 256 * 256 * lenData.at(0);
      const uint64_t val3 = 256 * lenData.at(1);
      const uint64_t val4 = lenData.at(2);

      const uint64_t trackUSecsPerQuarter = val2 + val3 + val4;
      if (uSecsPerQuarter < trackUSecsPerQuarter)
         uSecsPerQuarter = trackUSecsPerQuarter;

      return MetaEvent::Tempo;
   }
   else if (isMetaEvent(MetaEvent::LiveTag))
   {
      const uint64_t length = variableLength(trackChunkData, cursor);
      cursor += 1;      // tag
      cursor += length; // text

      return MetaEvent::LiveTag;
   }
   else
   {
      if (verbose)
         std::cout << __FUNCTION__ << " " << (uint16_t)subMarker << std::endl;
      assert(false);
   }

   return MetaEvent::MetaUnkown;
}

uint8_t Midi::File::Reader::compileMidiEventLength(const uint8_t marker) const
{
   // clang-format off
   static const std::map<uint8_t, uint8_t> messageStaticLengthMap =
      {
         {(uint8_t)Event::NoteOff, 3},
         {(uint8_t)Event::NoteOn, 3},
         {(uint8_t)Event::PolyKeyPressure, 3},
         {(uint8_t)Event::ControlChange, 3},
         {(uint8_t)Event::ProgrammChange, 2},
         {(uint8_t)Event::ChannelPressure, 2},
         {(uint8_t)Event::PitchBend, 3},
         // system common
         {(uint8_t)Event::QuarterFrame, 2},
         {(uint8_t)Event::SongPositionPointer, 3},
         {(uint8_t)Event::SongSelect, 2},
         {(uint8_t)Event::TuneRequest, 1},
         // system real time
         {(uint8_t)Event::Clock, 1},
         {(uint8_t)Event::Start, 1},
         {(uint8_t)Event::Continue, 1},
         {(uint8_t)Event::Stop, 1},
         {(uint8_t)Event::ActiveSensinig, 1},
         {(uint8_t)Event::Reset, 1}
      };
   // clang-format on

   const std::map<uint8_t, uint8_t>::const_iterator it = messageStaticLengthMap.find(marker & 0xf0);
   if (it == messageStaticLengthMap.cend())
      return 0;

   return it->second;
}

// see https://en.wikipedia.org/wiki/Variable-length_quantity
uint64_t Midi::File::Reader::variableLength(const Bytes& data, uint64_t& cursor) const
{
   uint64_t length = 0;

   uint8_t val = data.at(cursor);
   cursor += 1;

   length += removeFirstBit(val);

   while (hasFirstBit(val))
   {
      length *= 128;

      val = data.at(cursor);
      cursor += 1;

      length += removeFirstBit(val);
   }

   /*   
   std::vector<uint8_t> valList;
   for (size_t index = 0; true; index++)
   {
      uint8_t val = data.at(cursor + index);
      valList.push_back(removeFirstBit(val));
      if (!hasFirstBit(val)) // no following byte
         break;
   }

   uint64_t length = 0;
   uint32_t multiplier = 1;
   for (size_t index = valList.size() - 1; index >= 0; index--)
   {
      length += valList[index] * multiplier;
      multiplier *= 128;

      if (0 == index)
         break;
   }

   cursor += valList.size();
   */
   return length;
}

// file writer

#endif // NOT MidiFileHPP
