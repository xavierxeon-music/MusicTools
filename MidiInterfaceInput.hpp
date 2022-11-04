#ifndef MidiInterfaceInputHPP
#define MidiInterfaceInputHPP

#include <Midi/MidiInterfaceInput.h>

Midi::Interface::Input::Input()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllerChangeFunctionList()
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

bool Midi::Interface::Input::isOpen() const
{
   return false;
}

template <typename ClassType>
void Midi::Interface::Input::onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

void Midi::Interface::Input::noteOn(const Channel& channel, const Note& note, const Velocity& velocity)
{
   for (const NoteOnFunction& noteOnFunction : noteOnFunctionList)
      noteOnFunction(channel, note, velocity);
}

template <typename ClassType>
void Midi::Interface::Input::onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

void Midi::Interface::Input::noteOff(const Channel& channel, const Note& note)
{
   for (const NoteOffFunction& noteOffFunction : noteOffFunctionList)
      noteOffFunction(channel, note);
}

template <typename ClassType>
void Midi::Interface::Input::onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const ControllerMessage&, const uint8_t&))
{
   ControllerChangeFunction controllerChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllerChangeFunctionList.push_back(controllerChangeFunction);
}

void Midi::Interface::Input::controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)
{
   for (const ControllerChangeFunction& controllerChangeFunction : controllerChangeFunctionList)
      controllerChangeFunction(channel, controllerMessage, value);
}

template <typename ClassType>
void Midi::Interface::Input::onClockTick(ClassType* instance, void (ClassType::*functionPointer)())
{
   ClockTickFunction clockTickFunction = std::bind(functionPointer, instance);
   clockTickFunctionList.push_back(clockTickFunction);
}

void Midi::Interface::Input::clockTick()
{
   for (const ClockTickFunction& clockTickFunction : clockTickFunctionList)
      clockTickFunction();
}

template <typename ClassType>
void Midi::Interface::Input::onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&))
{
   ClockStatusFunction clockStatusFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   clockStatusFunctionList.push_back(clockStatusFunction);
}

void Midi::Interface::Input::clockStatus(const Playback& status)
{
   for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
      clockStatusFunction(status);
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
      const Channel channel = 1 + (message[0] & 0x0F);

      if (Event::NoteOn == event)
      {
         const Note note = Note::fromMidi(message[1]);
         const Velocity velocity = message[2];
         noteOn(channel, note, velocity);
      }
      else if (Event::NoteOff == event)
      {
         const Note note = Note::fromMidi(message[1]);
         noteOff(channel, note);
      }
      else if (Event::ControlChange == event)
      {
         const ControllerMessage controllerMessage = static_cast<ControllerMessage>(message[1]);
         const uint8_t value = message[2];
         controllerChange(channel, controllerMessage, value);
      }
   }
   else
   {
      const Event event = static_cast<Event>(message[0]);

      if (Event::SongPositionPointer == event)
      {
         uint16_t front = static_cast<uint16_t>(message.at(1));
         uint16_t back = static_cast<uint16_t>(message.at(2));

         const uint16_t songPosition = 1 + front + (128 * back);
         (void)songPosition;
      }
      else if (Event::Clock == event)
      {
         clockTick();
      }
      else if (Event::Start == event)
      {
         clockStatus(Playback::Start);
      }
      else if (Event::Continue == event)
      {
         clockStatus(Playback::Continue);
      }
      else if (Event::Stop == event)
      {
         clockStatus(Playback::Stop);
      }
   }
}

#endif // NOT MidiInterfaceInputHPP
