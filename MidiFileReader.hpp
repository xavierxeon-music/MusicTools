#ifndef MidiFileReaderHPP
#define MidiFileReaderHPP

#include <Midi/MidiFileReader.h>

#include <algorithm>

const static bool verbose = false;

Midi::FileReader::FileReader()
   : Replay()
{
}

bool Midi::FileReader::load(const Bytes& content)
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
      return false;

   const size_t maxIndex = chunkList.size();
   for (size_t index = 1; index < maxIndex; index++)
   {
      if (verbose)
         std::cout << "**** track #" << index << std::endl;
      const Chunk& trackChunk = chunkList.at(index);
      readTrack(trackChunk);
   }

   return true;
}

void Midi::FileReader::readHeader(const Chunk& headerChunk)
{
   if ("MThd" != headerChunk.id || 6 != headerChunk.data.size())
      return;

   const uint8_t div1 = headerChunk.data.at(4);
   const uint8_t div2 = headerChunk.data.at(5);

   const bool isSMPTE = hasCheck(div1);
   if (isSMPTE)
   {
      // TODO
      assert(false);
   }
   else
   {
      const uint16_t ticksPerQuarter = removeCheck(div1) * 256 + div2;
      ticksPer16 = ticksPerQuarter / 4;
   }
}

void Midi::FileReader::readTrack(const Chunk& trackChunk)
{
   // clang-format off
   static const std::map<uint8_t, uint64_t> messageStaticLengthMap =
   {
      {(uint8_t)Event::ControlChange, 2},
      {(uint8_t)Event::ProgrammChange, 1},
      {(uint8_t)Event::PolyKeyPressure, 2},
   };
   // clang-format on

   if ("MTrk" != trackChunk.id)
      return;

   Track track;

   Time fileTick = 0;
   uint64_t cursor = 0;
   const uint64_t maxCursor = trackChunk.data.size();

   Time lastNoteOnTick;
   Time lastNoteOffTick;
   while (cursor < maxCursor)
   {
      const Time tickDiff = variableLength(trackChunk.data, cursor);
      fileTick += tickDiff;

      if (cursor >= maxCursor)
         break;

      const uint8_t marker = trackChunk.data.at(cursor);
      cursor += 1;

      const bool isSystemEvent = (0xf0 == (marker & 0xf0));

      auto isEvent = [&](const Event mask)
      {
         if (isSystemEvent)
            return (mask == (mask & marker));
         else
            return (mask == (marker & 0xf0));
      };

      if (verbose)
         std::cout << __FUNCTION__ << " @ " << cursor << " 0x" << std::hex << (uint16_t)marker << std::dec << "  ";

      if (messageStaticLengthMap.find(marker) != messageStaticLengthMap.end())
      {
         const uint64_t length = messageStaticLengthMap.at(marker);
         cursor += length;

         if (verbose)
            std::cout << length << std::endl;
      }
      else if (isEvent(Event::Meta))
      {
         MetaEvent me = readMetaEvent(trackChunk.data, cursor, &track);
         if (verbose)
            std::cout << "meta event 0x" << std::hex << (uint16_t)me << std::dec << std::endl;
         if (MetaEvent::EndOfTrack == me)
            break;
      }
      else if (isEvent(Event::NoteOn))
      {
         NoteEvent noteOnEvent;
         noteOnEvent.channel = 0x0f & marker;
         noteOnEvent.key = trackChunk.data.at(cursor + 0);
         noteOnEvent.velocity = trackChunk.data.at(cursor + 1);
         cursor += 2;

         track.noteOnEventMap[fileTick].push_back(noteOnEvent);
         lastNoteOnTick = fileTick;

         if (verbose)
            std::cout << "note on" << std::endl;
      }
      else if (isEvent(Event::NoteOff))
      {
         NoteEvent noteOffEvent;
         noteOffEvent.channel = 0x0f & marker;
         noteOffEvent.key = trackChunk.data.at(cursor + 0);
         noteOffEvent.velocity = trackChunk.data.at(cursor + 1);
         cursor += 2;

         track.noteOffEventMap[fileTick].push_back(noteOffEvent);
         lastNoteOffTick = fileTick;

         if (verbose)
            std::cout << "note off " << std::endl;
      }
      else
      {
         if (verbose)
            std::cout << "UNKOWN" << std::endl;
         assert(false);
      }
   }

   if (0 != track.noteOnEventMap.size())
   {
      uint64_t maxTick = fileTick;
      if (0 != lastNoteOffTick && lastNoteOnTick < lastNoteOffTick)
         maxTick = lastNoteOffTick;

      track.header.maxTick = maxTick;
      trackList.push_back(track);

      const uint64_t barCounter = maxTick / (16 * ticksPer16);
      std::cout << barCounter << std::endl;
   }
}

Midi::MetaEvent Midi::FileReader::readMetaEvent(const Bytes& trackChunkData, uint64_t& cursor, Track* track)
{
   // clang-format off
   static const std::map<uint8_t, uint64_t> messageStaticLengthMap =
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

      //std::cout << std::string(text.cbegin(), text.cend()) << std::endl;

      if (MetaEvent::TrackName == (MetaEvent)subMarker && track)
         track->header.name = std::string(text.begin(), text.end());

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

bool Midi::FileReader::hasCheck(const uint8_t value) const
{
   static const uint8_t checkMask = 0x80; // bit 7 only

   bool test = ((value & checkMask) == checkMask);
   return test;
}

uint8_t Midi::FileReader::removeCheck(const uint8_t value) const
{
   static const uint8_t valueMask = 0x7f; // all but bit 7

   return (value & valueMask);
}

uint64_t Midi::FileReader::variableLength(const Bytes& data, uint64_t& cursor) const
{
   std::vector<uint8_t> valList;
   for (size_t index = 0; true; index++)
   {
      uint8_t val = data.at(cursor + index);
      valList.push_back(removeCheck(val));
      if (!hasCheck(val))
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
   return length;
}

#endif // NOT MidiFileReaderHPP
