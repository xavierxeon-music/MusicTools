#ifndef MidiInterfaceHPP
#define MidiInterfaceHPP

#include <Midi/MidiInterface.h>

Midi::Interface::Interface()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllChangeFunctionList()
   , passthroughList()
{
}

Midi::Interface::~Interface()
{
}

void Midi::Interface::initMidi(bool verbose)
{
   (void)verbose;
   // do nothing
}

void Midi::Interface::sendNoteOn(const Channel& channel, const Note& note, const Velocity& velocity)
{
   //qDebug() << "NOTE ON" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer << (Event::NoteOn | channel);
   buffer << note.midiValue;
   buffer << velocity;

   sendBuffer(buffer);
}

void Midi::Interface::sendNoteOff(const Channel& channel, const Note& note)
{
   //qDebug() << "NOTE OFF" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer << (Event::NoteOff | channel);
   buffer << note.midiValue;
   buffer << 127;

   sendBuffer(buffer);
}

void Midi::Interface::sendControllerChange(const Channel& channel, const ControllerMessage& cotrollerMessage, const uint8_t& value)
{
   Bytes buffer;

   buffer << (Event::ControlChange | channel);
   buffer << cotrollerMessage;
   buffer << value;

   sendBuffer(buffer);
}

template <typename ClassType>
void Midi::Interface::onReceiveNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

template <typename ClassType>
void Midi::Interface::onReceiveNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

template <typename ClassType>
void Midi::Interface::onReceiveControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const ControllerMessage&, const uint8_t&))
{
   ControllChangeFunction controllChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllChangeFunctionList.push_back(controllChangeFunction);
}

void Midi::Interface::addPassThroughInterface(Interface* passthrough)
{
   passthroughList.push_back(passthrough);
}

#endif // NOT MidiInterfaceHPP
