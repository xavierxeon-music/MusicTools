#ifndef MidiToolTempoHPP
#define MidiToolTempoHPP

#include <Midi/MidiToolTempo.h>

Midi::Tool::Tempo::Tempo(Interface::Input* input)
   : tickCounter(0)
{
   input->onNoteOn(this, &Tempo::noteOn);
   input->onClockTick(this, &Tempo::clockTick);
   input->onClockStatus(this, &Tempo::clockStatus);
}

void Midi::Tool::Tempo::noteOn(const Channel& channel, const Note& note, const Velocity& velocity)
{
   Q_UNUSED(note)
   Q_UNUSED(velocity)

   qDebug() << tickCounter << channel;
   tickCounter = 0;
}

void Midi::Tool::Tempo::clockTick()
{
   tickCounter++;
}

void Midi::Tool::Tempo::clockStatus(const Playback& status)
{
   if (Playback::Start == status)
      tickCounter = 0;
}

#endif // NOT MidiToolTempoHPP
