#ifndef MidiDeviceFlameCCH
#define MidiDeviceFlameCCH

#include <Midi/MidiInterface.h>

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

namespace Midi
{
   namespace Device
   {
      class FlameCC
      {
      public:

      public:
         inline FlameCC(Midi::Interface* midiInterface, const Channel& channel = 7);

      public:
         inline void sendSysEx();                        // midi port 0-15
         inline void setCV(uint8_t output, float voltage); // output 0-15, voltage between 0.0V and 5.0V

      private:
         Midi::Interface* midiInterface;
         const Channel midiChannel;
      };
   } // namespace Device
} // namespace Midi

#ifndef MidiDeviceFlameCCHPP
#include "../MidiDeviceFlameCC.hpp"
#endif // NOT MidiDeviceFlameCCHPP

#endif // MidiDeviceFlameCCH
