#ifndef MidiInterfaceInputHPP
#define MidiInterfaceInputHPP

#include <Midi/MidiInterfaceInput.h>

Midi::Interface::Input::Input()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllChangeFunctionList()
   , passthroughList()
{
}

Midi::Interface::Input::~Input()
{
}

template <typename ClassType>
void Midi::Interface::Input::onReceiveNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onReceiveNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onReceiveControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const ControllerMessage&, const uint8_t&))
{
   ControllChangeFunction controllChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllChangeFunctionList.push_back(controllChangeFunction);
}

void Midi::Interface::Input::addPassThroughInterface(Interface::Output* passthrough)
{
   passthroughList.push_back(passthrough);
}

#endif // NOT MidiInterfaceInputHPP
