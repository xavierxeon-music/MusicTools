#ifndef MidiToolTempoH
#define MidiToolTempoH

#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

#include <Music/Tempo.h>
namespace Base
{
   using Tempo = ::Tempo;
}

#include <Midi/MidiInterfaceInput.h>
#include <Tools/Counter.h>

namespace Midi
{
   namespace Tool
   {
      class Tempo : public Base::Tempo
      {
      public:
         inline Tempo(Interface::Input* input);

      public:
         inline bool isTick() const; // 4ppQ tick, e.e 16th notes
         inline bool isReset() const;

      private:
         using Base::Tempo::clockReset; // make private
         using Base::Tempo::clockTick;  // make private
         inline void midiClockTick();
         inline void midiClockStatus(const Playback& status);

      private:
         Counter tickCounter;
         bool isClockTick;
      };
   } // namespace Tool
} // namespace Midi

#ifndef MidiToolTempoHPP
#include "../../MidiToolTempo.hpp"
#endif // NOT MidiToolTempoHPP

#endif // NOT MidiToolTempoH
