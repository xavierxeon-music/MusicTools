#ifndef MidiInterfaceInputHPP
#define MidiInterfaceInputHPP

#include <Midi/MidiInterfaceInput.h>

Midi::Interface::Input::Input()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllChangeFunctionList()
   , clockTickFunctionList()
   , clockStatusFunctionList()
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
void Midi::Interface::Input::onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const ControllerMessage&, const uint8_t&))
{
   ControllChangeFunction controllChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllChangeFunctionList.push_back(controllChangeFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onClockTick(ClassType* instance, void (ClassType::*functionPointer)())
{
   ClockTickFunction clockTickFunction = std::bind(functionPointer, instance);
   clockTickFunctionList.push_back(clockTickFunction);
}

template <typename ClassType>
void Midi::Interface::Input::onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&))
{
   ClockStatusFunction clockStatusFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   clockStatusFunctionList.push_back(clockStatusFunction);
}

void Midi::Interface::Input::addPassThroughInterface(Interface::Output* passthrough)
{
   passthroughList.push_back(passthrough);
}

void Midi::Interface::Input::dataFromInput(const Bytes& message)
{
   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Event event = static_cast<Event>(message[0] & 0xF0);
      const Channel channel = message[0] & 0x0F;

      if (Event::NoteOn == event)
      {
         const Note note = Note::fromMidi(message[1]);
         const Velocity velocity = message[2];

         for (const NoteOnFunction& noteOnFunction : noteOnFunctionList)
            noteOnFunction(channel, note, velocity);
      }
      else if (Event::NoteOff == event)
      {
         const Note note = Note::fromMidi(message[1]);

         for (const NoteOffFunction& noteOffFunction : noteOffFunctionList)
            noteOffFunction(channel, note);
      }
      else if (Event::ControlChange == event)
      {
         const ControllerMessage controllerMessage = static_cast<ControllerMessage>(message[1]);
         const uint8_t value = message[2];

         for (const ControllChangeFunction& controllChangeFunction : controllChangeFunctionList)
            controllChangeFunction(channel, controllerMessage, value);
      }
   }
   else
   {
      const Event event = static_cast<Event>(message[0]);

      if (Midi::Event::SongPositionPointer == event)
      {
         qDebug() << "song pos";
      }
      else if (Midi::Event::Clock == event)
      {
         for (const ClockTickFunction& clockTickFunction : clockTickFunctionList)
            clockTickFunction();
      }
      else if (Midi::Event::Start == event)
      {
         for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
            clockStatusFunction(Playback::Start);
      }
      else if (Midi::Event::Continue == event)
      {
         for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
            clockStatusFunction(Playback::Continue);
      }
      else if (Midi::Event::Stop == event)
      {
         for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
            clockStatusFunction(Playback::Stop);
      }
   }
}

#endif // NOT MidiInterfaceInputHPP
