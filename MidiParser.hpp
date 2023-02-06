#ifndef MidiParserHPP
#define MidiParserHPP

#include <Midi/MidiParser.h>

Midi::Parser::Parser()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllerChangeFunctionList()
   , clockTickFunctionList()
   , clockStatusFunctionList()
{
}

void Midi::Parser::prcocess(const Bytes& message)
{
   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Event event = static_cast<Event>(message[0] & 0xF0);
      const Channel channel = 1 + (message[0] & 0x0F);

      if (Event::NoteOn == event)
      {
         const uint8_t midiNote = message[1];
         const Velocity velocity = message[2];
         noteOn(channel, midiNote, velocity);
      }
      else if (Event::NoteOff == event)
      {
         const uint8_t midiNote = message[1];
         noteOff(channel, midiNote);
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

         const uint16_t position = 1 + front + (128 * back);
         songPosition(position);
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

template <typename ClassType>
void Midi::Parser::onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

template <typename ClassType>
void Midi::Parser::onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

template <typename ClassType>
void Midi::Parser::onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const ControllerMessage&, const uint8_t&))
{
   ControllerChangeFunction controllerChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllerChangeFunctionList.push_back(controllerChangeFunction);
}

template <typename ClassType>
void Midi::Parser::onClockTick(ClassType* instance, void (ClassType::*functionPointer)())
{
   ClockTickFunction clockTickFunction = std::bind(functionPointer, instance);
   clockTickFunctionList.push_back(clockTickFunction);
}

template <typename ClassType>
void Midi::Parser::onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&))
{
   ClockStatusFunction clockStatusFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   clockStatusFunctionList.push_back(clockStatusFunction);
}

template <typename ClassType>
void Midi::Parser::onSongPosition(ClassType* instance, void (ClassType::*functionPointer)(const uint16_t&))
{
   SongPositionFunction songPositionFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   songPositionFunctionList.push_back(songPositionFunction);
}

void Midi::Parser::noteOn(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity)
{
   for (const NoteOnFunction& noteOnFunction : noteOnFunctionList)
      noteOnFunction(channel, midiNote, velocity);
}

void Midi::Parser::noteOff(const Channel& channel, const uint8_t& midiNote)
{
   for (const NoteOffFunction& noteOffFunction : noteOffFunctionList)
      noteOffFunction(channel, midiNote);
}

void Midi::Parser::controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)
{
   for (const ControllerChangeFunction& controllerChangeFunction : controllerChangeFunctionList)
      controllerChangeFunction(channel, controllerMessage, value);
}

void Midi::Parser::clockTick()
{
   for (const ClockTickFunction& clockTickFunction : clockTickFunctionList)
      clockTickFunction();
}

void Midi::Parser::clockStatus(const Playback& status)
{
   for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
      clockStatusFunction(status);
}

void Midi::Parser::songPosition(const uint16_t& position)
{
   for (const SongPositionFunction& songPositionFunction : songPositionFunctionList)
      songPositionFunction(position);
}

#endif // NOT MidiParserHPP
