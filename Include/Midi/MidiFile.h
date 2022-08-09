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

} // namespace Midi

#ifndef MidiFileHPP
#include "../../MidiFile.hpp"
#endif // NOT MidiFileHPP

#endif // NOT MidiFileH
