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
   // do nothing
}

void Midi::Interface::Input::open()
{
   // do nothing
}

void Midi::Interface::Input::close()
{
   // do nothing
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

void Midi::Interface::Input::dataFromInput(const Bytes& message)
{
   if (message.size() != 3)
      return;

   const Midi::Channel channel = message[0] & 0x0F;
   if (Midi::Event::NoteOn == (message[0] & 0xF0))
   {
      const Note note = Note::fromMidi(message[1]);
      const Midi::Velocity velocity = message[2];

      for (const NoteOnFunction& noteOnFunction : noteOnFunctionList)
         noteOnFunction(channel, note, velocity);
   }
   else if (Midi::Event::NoteOff == (message[0] & 0xF0))
   {
      const Note note = Note::fromMidi(message[1]);

      for (const NoteOffFunction& noteOffFunction : noteOffFunctionList)
         noteOffFunction(channel, note);
   }
   else if (Midi::Event::ControlChange == (message[0] & 0xF0))
   {
      const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(message[1]);
      const uint8_t value = message[2];

      for (const ControllChangeFunction& controllChangeFunction : controllChangeFunctionList)
         controllChangeFunction(channel, controllerMessage, value);
   }
}

#endif // NOT MidiInterfaceInputHPP
