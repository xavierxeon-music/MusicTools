#ifndef MidiFileReaderH
#define MidiFileReaderH

#include <Midi/MidiFile.h>

namespace Midi
{
   namespace File
   {
      class Reader : public Sequence
      {
      public:
         inline Reader(const Bytes& content);

      private:
         // workflow
         inline void readHeader(const Chunk& headerChunk);
         inline void readTrack(const Chunk& trackChunk);
         inline MetaEvent readMetaEvent(const Bytes& trackChunkData, uint64_t& cursor, Track* track = nullptr);

         // utilities
         inline bool hasCheck(const uint8_t value) const;
         inline uint8_t removeCheck(const uint8_t value) const;
         inline uint64_t variableLength(const Bytes& data, uint64_t& cursor) const;

         inline void updateMonophonicFlag();
      };
   } // namespace File
} // namespace Midi

#ifndef MidiFileReaderHPP
#include "../../MidiFileReader.hpp"
#endif // NOT MidiFileReaderHPP

#endif // NOT MidiFileReaderH
