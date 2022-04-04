#ifndef MidiToolTempoHPP
#define MidiToolTempoHPP

#include <Midi/MidiToolTempo.h>

Midi::Tool::Tempo::Tempo(Interface::Input* input)
   : tickCounter(0)
{
   input->onClockTick(this, &Tempo::clockTick);
   input->onClockStatus(this, &Tempo::clockStatus);
}


void Midi::Tool::Tempo::clockTick()
{
   tickCounter++;
   if (6 == tickCounter)
   {
      tickCounter = 0;
   }
}

void Midi::Tool::Tempo::clockStatus(const Playback& status)
{
   if (Playback::Start == status)
      tickCounter = 0;
}

#endif // NOT MidiToolTempoHPP
