#ifndef MidiDeviceDoepferQuadHPP
#define MidiDeviceDoepferQuadHPP

#include <Midi/MidiDeviceDoepferQuad.h>

#include <Tools/Range.h>

// strip

Midi::Device::DoepferQuad::Strip::Strip()
   : midiInterface(nullptr)
   , midiChannel(0)
   , controllerMessage(Midi::ControllerMessage::AllNotesOff)
   , note(Note::fromVoltage(0))
   , velocity(0)
   , controllerValue(0)
{
}

Midi::Device::DoepferQuad::Strip::Strip(Midi::Interface* midiInterface, const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage)
   : midiInterface(midiInterface)
   , midiChannel(midiChannel)
   , controllerMessage(controllerMessage)
   , note(Note::fromVoltage(0))
   , velocity(0)
   , controllerValue(0)
{
}

void Midi::Device::DoepferQuad::Strip::setCV(uint8_t output, float voltage)
{
   const float value = voltage * 0.2 * 127.0;
   const uint8_t iValue = Range::clamp<uint8_t>(value, 0, 127);

   if (0 == output)
      note = Note::fromVoltage(voltage);
   else if (1 == output)
      velocity = iValue;
   else if (2 == output)
      controllerValue = iValue;

   midiInterface->sendNoteOn(midiChannel, note, velocity);
   midiInterface->sendControllerChange(midiChannel, controllerMessage, controllerValue);
}

// device

Midi::Device::DoepferQuad::DoepferQuad(Midi::Interface* midiInterface)
   : midiInterface(midiInterface)
{
}

Midi::Device::DoepferQuad::Strip Midi::Device::DoepferQuad::create(const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage)
{
   return Strip(midiInterface, midiChannel, controllerMessage);
}

#endif // NOT MidiDeviceDoepferQuadHPP
