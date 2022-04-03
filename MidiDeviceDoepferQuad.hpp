#ifndef MidiDeviceDoepferQuadHPP
#define MidiDeviceDoepferQuadHPP

#include <Midi/MidiDeviceDoepferQuad.h>

// strip

Midi::Device::DoepferQuad::Strip::Strip()
   : midiInterface(nullptr)
   , midiChannel(0)
   , controllerMessage(Midi::ControllerMessage::AllNotesOff)
   , prevNote()
{
}

Midi::Device::DoepferQuad::Strip::Strip(Midi::Interface* midiInterface, const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage, const uint8_t refNote)
   : midiInterface(midiInterface)
   , midiChannel(midiChannel)
   , controllerMessage(controllerMessage)
   , noteDiff(0)
   , prevNote()
{
   noteDiff = Note::availableNotes[1].midiValue - refNote;
}

void Midi::Device::DoepferQuad::Strip::setCV12(float voltage1, float voltage2)
{
   Note note = Note::fromVoltage(voltage1);
   note.midiValue = note.midiValue - noteDiff;

   const Velocity velocity = static_cast<uint8_t>(mapper(voltage2));

   midiInterface->sendNoteOff(midiChannel, prevNote);
   midiInterface->sendNoteOn(midiChannel, note, velocity);

   prevNote = note;
}

void Midi::Device::DoepferQuad::Strip::setCV3(float voltage3)
{
   const uint8_t controllerValue = static_cast<uint8_t>(mapper(voltage3));

   midiInterface->sendControllerChange(midiChannel, controllerMessage, controllerValue);
}

// device

Midi::Device::DoepferQuad::DoepferQuad(Midi::Interface* midiInterface)
   : midiInterface(midiInterface)
{
}

Midi::Device::DoepferQuad::Strip Midi::Device::DoepferQuad::create(const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage, const uint8_t refNote)
{
   midiInterface->sendControllerChange(midiChannel, Midi::ControllerMessage::AllNotesOff, 0);
   return Strip(midiInterface, midiChannel, controllerMessage, refNote);
}

#endif // NOT MidiDeviceDoepferQuadHPP
