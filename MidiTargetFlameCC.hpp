#ifndef MidiTargetFlameCCHPP
#define MidiTargetFlameCCHPP

#include <Midi/MidiTargetFlameCC.h>

#include <Tools/Range.h>

Midi::Target::FlameCC::FlameCC(Interface::Output* midiOutput, const Channel& midiChannel)
   : midiOutput(midiOutput)
   , midiChannel(midiChannel)
{
}

void Midi::Target::FlameCC::init()
{
   midiOutput->sendControllerChange(midiChannel, ControllerMessage::AllNotesOff, 0);

   for (uint8_t output = 0; output < 16; output++)
   {
      const Note note = Note::fromMidi(41 + output); // note F2
      midiOutput->sendNoteOn(midiChannel, note, 127);
   }
}

void Midi::Target::FlameCC::setCV(uint8_t output, float voltage)
{
   const uint8_t message = ControllerMessage::User01 + Range::clamp<uint8_t>(output, 0, 15);
   const uint8_t value = static_cast<uint8_t>(mapper(voltage));

   midiOutput->sendControllerChange(midiChannel, static_cast<ControllerMessage>(message), value);
}

void Midi::Target::FlameCC::sendSysEx()
{
   Bytes buffer(38);

   buffer[0] = static_cast<uint8_t>(Midi::Event::System); // Exclusive Status
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

   buffer[37] = static_cast<uint8_t>(Midi::Event::SysExEnd); // End of Exclusive

   midiOutput->sendBuffer(buffer);
}

#endif // MidiTargetFlameCCHPP
