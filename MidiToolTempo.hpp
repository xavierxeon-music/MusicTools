#ifndef MidiToolTempoHPP
#define MidiToolTempoHPP

#include <Midi/MidiToolTempo.h>

Midi::Tool::Tempo::Tempo(Interface::Input* input)
   : Base::Tempo()
   , tickCounter(6)
   , isClockTick(false)
{
   input->onClockTick(this, &Tempo::midiClockTick);
   input->onClockStatus(this, &Tempo::midiClockStatus);
}

bool Midi::Tool::Tempo::isTick() const
{
   return isClockTick;
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

   if (0 == tickCounter.valueAndNext())
   {
      isClockTick = true;
      clockTick();
   }
   else
      isClockTick = false;
}

void Midi::Tool::Tempo::midiClockStatus(const Playback& status)
{
   if (Playback::Start == status)
   {
      clockReset();
      tickCounter.reset();
      runState = RunState::Reset;
   }
}

#endif // NOT MidiToolTempoHPP
