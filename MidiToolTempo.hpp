#ifndef MidiToolTempoHPP
#define MidiToolTempoHPP

#include <Midi/MidiToolTempo.h>

Midi::Tool::Tempo::Tempo(Interface::Input* input)
   : Base::Tempo()
   , tickCounter(0)
{
   input->onClockTick(this, &Tempo::midiClockTick);
   input->onClockStatus(this, &Tempo::midiClockStatus);
}

bool Midi::Tool::Tempo::isTick() const
{
   return (0 == tickCounter);
}

bool Midi::Tool::Tempo::isReset() const
{
   return (RunState::Reset == runState);
}

void Midi::Tool::Tempo::midiClockTick()
{
   if (RunState::Off == runState || RunState::Reset == runState)
      runState = RunState::FirstTick;
   else if (RunState::FirstTick == runState)
      runState = RunState::Running;

   tickCounter++;
   if (6 == tickCounter)
   {
      clockTick();
      tickCounter = 0;
   }
}

void Midi::Tool::Tempo::midiClockStatus(const Playback& status)
{
   if (Playback::Start == status)
   {
      clockReset();
      tickCounter = 0;
      runState = RunState::Reset;
   }
}

#endif // NOT MidiToolTempoHPP
