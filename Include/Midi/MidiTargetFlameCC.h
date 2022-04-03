#ifndef MidiTargetFlameCCH
#define MidiTargetFlameCCH

#include <Midi/MidiInterfaceOutput.h>

/* --------- !! IMPORTANT !! ---------
Daisy Pahch uses TRS A, whereas FlameCC uses TRS B
see https://minimidi.world

either use a [TRS A to MIDI] -> [Midi Cable] -> [TRS B to MIDI],

or make your own custom cable
  Type A          Type B
 Sink   /_\     Source /_\
 Source |_|     Sink   |_|
 Shield | |     Shield | |
*/

#include <Tools/Range.h>

namespace Midi
{
   namespace Target
   {
      class FlameCC
      {
      public:

      public:
         inline FlameCC(Interface::Output* midiOutput, const Channel& channel = 12);

      public:
         inline void init();
         inline void setCV(uint8_t output, float voltage); // output 0-15, voltage between 0.0V and 5.0V
         inline void sendSysEx();                          // midi port 0-15

      private:
         Interface::Output* midiOutput;
         const Channel midiChannel;

         inline static const Range::Mapper mapper = Range::Mapper(0.0, 5.0, 0.0, 127.0);
      };
   } // namespace Target
} // namespace Midi

#ifndef MidiTargetFlameCCHPP
#include "../MidiTargetFlameCC.hpp"
#endif // NOT MidiTargetFlameCCHPP

#endif // MidiTargetFlameCCH
