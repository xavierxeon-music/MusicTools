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
         class NoteGatePair
         {
         public:
            inline void noteOn(const Note& note);
            inline void noteOff(const Note& note);

         private:
            friend class FlameCC;

         private:
            inline NoteGatePair(FlameCC* parent, uint8_t pitchOutput, uint8_t gateOutput);

         private:
            FlameCC* parent;
            uint8_t pitchOutput;
            uint8_t gateOutput;
         };

      public:
         inline FlameCC(Midi::Interface* midiInterface, const Channel& channel = 3);

      public:
         inline void sendSysEx();                        // midi port 0-15
         inline void setCV(uint8_t output, float value); // output 0-15, value between 0.0 and 1.0
         inline NoteGatePair* createPair(uint8_t pitchOutput, uint8_t gateOutput);

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
