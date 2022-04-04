#ifndef MidiToolTempoH
#define MidiToolTempoH

#include <Midi/MidiInterfaceInput.h>

namespace Midi
{
   namespace Tool
   {
      class Tempo
      {
      public:
         inline Tempo(Interface::Input* input);

      private:
         inline void noteOn(const Channel& channel, const Note& note, const Velocity& velocity);
         inline void clockTick();
         inline void clockStatus(const Playback& status);

      private:
         uint8_t tickCounter;
      };
   } // namespace Tool
} // namespace Midi

#ifndef MidiToolTempoHPP
#include "../../MidiToolTempo.hpp"
#endif // NOT MidiToolTempoHPP

#endif // NOT MidiToolTempoH
