#ifndef MidiTargetDoepferQuadHPP
#define MidiTargetDoepferQuadHPP

#include <Midi/MidiTargetDoepferQuad.h>

// strip

Midi::Target::DoepferQuad::Strip::Strip()
   : midiOutput(nullptr)
   , midiChannel(0)
   , controllerMessage(ControllerMessage::AllNotesOff)
   , prevNote()
{
}

Midi::Target::DoepferQuad::Strip::Strip(Interface::Output* midiOutput, const Channel& midiChannel, const ControllerMessage& controllerMessage, const uint8_t refNote)
   : midiOutput(midiOutput)
   , midiChannel(midiChannel)
   , controllerMessage(controllerMessage)
   , noteDiff(0)
   , prevNote()
{
   noteDiff = Note::availableNotes[1].midiValue - refNote;
}

void Midi::Target::DoepferQuad::Strip::setCV12(float voltage1, float voltage2)
{
   Note note = Note::fromVoltage(voltage1);
   note.midiValue = note.midiValue - noteDiff;

   const Velocity velocity = static_cast<uint8_t>(mapper(voltage2));

   midiOutput->sendNoteOff(midiChannel, prevNote);
   midiOutput->sendNoteOn(midiChannel, note, velocity);

   prevNote = note;
}

void Midi::Target::DoepferQuad::Strip::setCV3(float voltage3)
{
   const uint8_t controllerValue = static_cast<uint8_t>(mapper(voltage3));

   midiOutput->sendControllerChange(midiChannel, controllerMessage, controllerValue);
}

// Target

Midi::Target::DoepferQuad::DoepferQuad(Midi::Interface::Output* midiOutput)
   : midiOutput(midiOutput)
{
}

Midi::Target::DoepferQuad::Strip Midi::Target::DoepferQuad::create(const Channel& midiChannel, const ControllerMessage& controllerMessage, const uint8_t refNote)
{
   midiOutput->sendControllerChange(midiChannel, Midi::ControllerMessage::AllNotesOff, 0);
   return Strip(midiOutput, midiChannel, controllerMessage, refNote);
}

#endif // NOT MidiTargetDoepferQuadHPP
