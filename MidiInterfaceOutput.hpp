#ifndef MidiInterfaceOutputHPP
#define MidiInterfaceOutputHPP

#include <Midi/MidiInterfaceOutput.h>

Midi::Interface::Output::Output()
{
}

Midi::Interface::Output::~Output()
{
}

void Midi::Interface::Output::sendNoteOn(const Channel& channel, const Note& note, const Velocity& velocity)
{
   //qDebug() << "NOTE ON" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer << (Event::NoteOn | channel);
   buffer << note.midiValue;
   buffer << velocity;

   sendBuffer(buffer);
}

void Midi::Interface::Output::sendNoteOff(const Channel& channel, const Note& note)
{
   //qDebug() << "NOTE OFF" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer << (Event::NoteOff | channel);
   buffer << note.midiValue;
   buffer << 127;

   sendBuffer(buffer);
}

void Midi::Interface::Output::sendControllerChange(const Channel& channel, const ControllerMessage& cotrollerMessage, const uint8_t& value)
{
   Bytes buffer;

   buffer << (Event::ControlChange | channel);
   buffer << cotrollerMessage;
   buffer << value;

   sendBuffer(buffer);
}

#endif // NOT MidiInterfaceOutputHPP
