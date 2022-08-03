#ifndef MidiFileReaderHPP
#define MidiFileReaderHPP

#include <Midi/MidiFileReader.h>

#include <algorithm>

Midi::FileReader::FileReader()
   : Replay()
{
}

bool Midi::FileReader::load(const Bytes& content)
{
   Chunk::List chunkList;

   uint64_t cursor = 0;

   auto subBytes = [&](const uint32_t length)
   {
      Bytes subData(content.begin() + cursor, content.begin() + cursor + length);
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

      uint32_t val1 = 256 * 256 * 256 * (uint8_t)lenData.at(0);
      uint32_t val2 = 256 * 256 * (uint8_t)lenData.at(1);
      uint32_t val3 = 256 * (uint8_t)lenData.at(2);
      uint32_t val4 = (uint8_t)lenData.at(3);
      uint32_t length = val1 + val2 + val3 + val4;

      chunk.data = subBytes(length);

      chunkList.push_back(chunk);
   }

   readHeader(chunkList.at(0));
   if (0 == ticksPer16)
      return false;

   const size_t maxIndex = chunkList.size();
   for (size_t index = 1; index < maxIndex; index++)
   {
      const Chunk& trackChunk = chunkList.at(index);
      readTrack(trackChunk);
   }

   return true;
}

void Midi::FileReader::readHeader(const Chunk& headerChunk)
{
   if ("MThd" != headerChunk.id || 6 != headerChunk.data.size())
      return;

   uint8_t div1 = headerChunk.data.at(4);
   uint8_t div2 = headerChunk.data.at(5);

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
   if ("MTrk" != trackChunk.id)
      return;

   Track track;

   Time fileTick = 0;
   uint64_t cursor = 0;
   const uint64_t maxCursor = trackChunk.data.size();
   while (cursor < maxCursor)
   {
      const uint32_t tickDiff = variableLength(trackChunk.data, cursor);
      fileTick += tickDiff;

      if (cursor >= maxCursor)
         break;

      const uint8_t marker = trackChunk.data.at(cursor);
      cursor += 1;

      if (fitMask((uint8_t)Event::Meta, marker))
      {
         MetaEvent me = metaEvent(trackChunk.data, cursor, &track);
         if (MetaEvent::EndOfTrack == me)
            break;
      }
      else if (fitMask((uint8_t)Event::NoteOn, marker))
      {
         NoteEvent noteEvent;
         noteEvent.channel = 0x0f & marker;
         noteEvent.key = trackChunk.data.at(cursor + 0);
         noteEvent.velocity = trackChunk.data.at(cursor + 1);
         cursor += 2;

         track.noteOnEventMap[fileTick].push_back(noteEvent);
      }
      else if (fitMask((uint8_t)Event::NoteOff, marker))
      {
         NoteEvent noteEvent;
         noteEvent.channel = 0x0f & marker;
         noteEvent.key = trackChunk.data.at(cursor + 0);
         noteEvent.velocity = trackChunk.data.at(cursor + 1);
         cursor += 2;

         track.noteOffEventMap[fileTick].push_back(noteEvent);
      }
      else
      {
         //assert(false);
      }
   }

   if (0 != track.noteOnEventMap.size())
   {
      track.header.maxTick = fileTick;
      trackList.push_back(track);
   }
}

Midi::MetaEvent Midi::FileReader::metaEvent(const Bytes& data, uint64_t& cursor, Track* track)
{
   const uint8_t subMarker = data.at(cursor);
   cursor += 1;

   using MarkerLengthMap = std::map<uint8_t, uint64_t>;
   using TextList = std::vector<uint8_t>;

   // clang-format off
   static const MarkerLengthMap markerLengthMap =
      {
         {(uint8_t)MetaEvent::ChannelPrefix, 2},
         {(uint8_t)MetaEvent::MidiPort, 1},
         {(uint8_t)MetaEvent::SMPTEOffset, 6},
         {(uint8_t)MetaEvent::TimeSignature, 5},
         {(uint8_t)MetaEvent::KeySignature, 3}
      };
   
   static const TextList lenTextList =
      {
         (uint8_t)MetaEvent::Copyright,
         (uint8_t)MetaEvent::TrackName,
         (uint8_t)MetaEvent::InstrumentName,
         (uint8_t)MetaEvent::Lyric,
         (uint8_t)MetaEvent::Marker,
         (uint8_t)MetaEvent::CuePoint
      };
   // clang-format on

   auto subBytes = [&](const uint32_t length)
   {
      Bytes subData(data.begin() + cursor, data.begin() + cursor + length);
      cursor += length;
      return subData;
   };

   if (markerLengthMap.find(subMarker) != markerLengthMap.end())
   {
      cursor += markerLengthMap.at(subMarker);
      return static_cast<MetaEvent>(subMarker);
   }
   else if (std::find(lenTextList.begin(), lenTextList.end(), subMarker) != lenTextList.end())
   {
      const uint32_t length = variableLength(data, cursor);
      const Bytes text = subBytes(length);

      if (MetaEvent::TrackName == (MetaEvent)subMarker && track)
         track->header.name = std::string(text.begin(), text.end());

      return static_cast<MetaEvent>(subMarker);
   }
   else if (fitMask((uint8_t)MetaEvent::EndOfTrack, subMarker))
   {
      cursor += 1;

      return MetaEvent::EndOfTrack;
   }
   else if (fitMask((uint8_t)MetaEvent::Tempo, subMarker))
   {
      const Bytes lenData = subBytes(4);

      uint32_t val1 = (uint8_t)lenData.at(0);
      (void)val1;

      uint32_t val2 = 256 * 256 * (uint8_t)lenData.at(1);
      uint32_t val3 = 256 * (uint8_t)lenData.at(2);
      uint32_t val4 = (uint8_t)lenData.at(3);
      uSecsPerQuarter = val2 + val3 + val4;

      return MetaEvent::Tempo;
   }
   else if (fitMask((uint8_t)MetaEvent::LiveTag, subMarker))
   {
      const uint32_t len = variableLength(data, cursor);
      cursor += 1;   // tag
      cursor += len; // text

      return MetaEvent::LiveTag;
   }
   else
   {
      //assert(false);
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

uint32_t Midi::FileReader::variableLength(const Bytes& data, uint64_t& cursor) const
{
   std::vector<uint8_t> valList;
   for (size_t index = 0; true; index++)
   {
      uint8_t val = data.at(cursor + index);
      valList.push_back(removeCheck(val));
      if (!hasCheck(val))
         break;
   }

   uint32_t length = 0;
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

bool Midi::FileReader::fitMask(const uint8_t mask, const uint8_t value) const
{
   return (mask == (mask & value));
}

#endif // NOT MidiFileReaderHPP
