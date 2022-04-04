#ifndef MidiToolGateHPP
#define MidiToolGateHPP

#include <Midi/MidiToolGate.h>

Midi::Tool::Gate::Gate(Interface::Input* input, const Channel& channel, const Note& note)
   : myChannel(channel)
   , myNote(note)
   , on(false)
{
   input->onNoteOn(this, &Gate::noteOn);
   input->onNoteOff(this, &Gate::noteOff);
}

bool Midi::Tool::Gate::isOn() const
{
   return on;
}

void Midi::Tool::Gate::noteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)
{
   Q_UNUSED(velocity)

   if (myChannel != channel)
      return;
   if (myNote.midiValue != note.midiValue)
      return;

   on = true;
}

void Midi::Tool::Gate::noteOff(const Midi::Channel& channel, const Note& note)
{
   if (myChannel != channel)
      return;
   if (myNote.midiValue != note.midiValue)
      return;

   on = false;
}

#endif // NOT MidiToolGateHPP
