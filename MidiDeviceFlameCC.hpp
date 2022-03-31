#ifndef MidiDeviceFlameCCHPP
#define MidiDeviceFlameCCHPP

#include <Midi/MidiDeviceFlameCC.h>
#include <Tools/Range.h>

// port pair

void Midi::Device::FlameCC::NoteGatePair::noteOn(const Note& note)
{
   parent->setCV(pitchOutput, note.voltage / 5.0);
   parent->setCV(gateOutput, 1.0);
}

void Midi::Device::FlameCC::NoteGatePair::noteOff(const Note& note)
{
   parent->setCV(pitchOutput, note.voltage / 5.0);
   parent->setCV(gateOutput, 0.0);
}

Midi::Device::FlameCC::NoteGatePair::NoteGatePair(FlameCC* parent, uint8_t pitchOutput, uint8_t gateOutput)
   : parent(parent)
   , pitchOutput(pitchOutput)
   , gateOutput(gateOutput)
{
}

// Device

Midi::Device::FlameCC::FlameCC(Interface* midiInterface, const Channel& midiChannel)
   : midiInterface(midiInterface)
   , midiChannel(midiChannel)
{
}

void Midi::Device::FlameCC::sendSysEx()
{
   Bytes buffer(38);

   buffer[0] = static_cast<uint8_t>(Midi::Event::SysExStart); // Exclusive Status
   buffer[1] = 0x7D; // Header Flame module
   buffer[2] = 0x0B; // Flame module “μ16MCC”
   buffer[3] = 0x01; // version 1
   buffer[4] = 0x06; // data type 1 (dump all data)

   for (uint8_t output = 0; output < 16; output++)
   {
      // MIDI channels for CV 16 outputs (range: 00=channel 1 .. 0F=channel 16)
      buffer[5 + output] = midiChannel;

      // control change numbers for 15 outputs
      const uint8_t message = static_cast<uint8_t>(ControllerMessage::User01) + output;
      buffer[21 + output] = message;
   }

   buffer[37] = static_cast<uint8_t>(Midi::Event::SysExStart); // End of Exclusive

   midiInterface->sendBuffer(buffer);
}

void Midi::Device::FlameCC::setCV(uint8_t output, float value)
{
   const Note note = Note::fromMidi(41 + output);

   const uint8_t message = ControllerMessage::User01 + Range::clamp<uint8_t>(output, 0, 15);
   const uint8_t iValue = Range::clamp<uint8_t>(value * 127, 0, 127);

   midiInterface->sendNoteOn(midiChannel, note, 127);
   midiInterface->sendControllerChange(midiChannel, static_cast<ControllerMessage>(message), iValue);
}

Midi::Device::FlameCC::NoteGatePair* Midi::Device::FlameCC::createPair(uint8_t pitchOutput, uint8_t gateOutput)
{
   return new NoteGatePair(this, pitchOutput, gateOutput);
}

#endif // MidiDeviceFlameCCHPP
