#ifndef MidiFileH
#define MidiFileH

#include <Blocks/Sequencer.h>
#include <Midi/MidiCommon.h>
#include <MusicTools.h>

// see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

pyexport namespace Midi
{
   pyexport class FileOld
   {
   public:
      class Reader;
      class Writer;

      pyexport inline static Sequencer load(const Bytes& content);
      pyexport inline static Bytes save(const Sequencer& seqeuencer);

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
