#ifndef MidiFileH
#define MidiFileH

#include <Blocks/Sequencer.h>

#include <Midi/MidiCommon.h>
#include <MusicTools.h>

// see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

namespace Midi
{
   class File
   {
   public:
      class Reader;
      class Writer;

      inline static Sequencer load(const Bytes& content);
      inline static Bytes save(const Sequencer& seqeuencer);

   protected:
      struct Chunk
      {
         std::string id;
         Bytes data;

         using List = std::vector<Chunk>;
      };

      const static bool verbose = false;
   };

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

#ifndef MidiFileHPP
#include "../../MidiFile.hpp"
#endif // NOT MidiFileHPP

#endif // NOT MidiFileH
