#ifndef MidiFileReaderH
#define MidiFileReaderH

#include <Blocks/Sequencer.h>
#include <Midi/MidiFile.h>

namespace Midi
{
   class File::Reader : public Sequencer, public File
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
   };
} // namespace Midi

#ifndef MidiFileReaderHPP
#include "../../MidiFileReader.hpp"
#endif // NOT MidiFileReaderHPP

#endif // NOT MidiFileReaderH
