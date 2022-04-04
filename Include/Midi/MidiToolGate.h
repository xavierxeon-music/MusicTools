#ifndef MidiToolGateH
#define MidiToolGateH

#include <Midi/MidiCommon.h>
#include <Midi/MidiInterfaceInput.h>

namespace Midi
{
   namespace Tool
   {
      class Gate
      {
      public:
         inline Gate(Interface::Input* input, const Channel& channel, const Note& note);

      public:
         inline bool isOn() const;

      private:
         inline void noteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity);
         inline void noteOff(const Midi::Channel& channel, const Note& note);

      private:
         const Channel myChannel;
         const Note myNote;

         bool on;
      };
   } // namespace Tool
} // namespace Midi

#ifndef MidiToolGateHPP
#include "../../MidiToolGate.hpp"
#endif // NOT MidiToolGateHPP

#endif // NOT MidiToolGateH
