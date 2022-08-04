#ifndef MidiFileReaderH
#define MidiFileReaderH

#include <Blocks/Replay.h>

#include <Midi/MidiCommon.h>
#include <MusicTools.h>

// see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

namespace Midi
{
   class FileReader : public Replay
   {
   public:
      inline FileReader();

   public:
      inline bool load(const Bytes& content);

   private:
      struct Chunk
      {
         std::string id;
         Bytes data;

         using List = std::vector<Chunk>;
      };

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
