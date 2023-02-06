#ifndef MidiParserH
#define MidiParserH

#include <functional>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>

namespace Midi
{
   class Parser
   {
   public:
      using NoteOnFunction = std::function<void(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity)>;
      using NoteOffFunction = std::function<void(const Channel& channel, const uint8_t& midiNote)>;
      using ControllerChangeFunction = std::function<void(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)>;
      using ClockTickFunction = std::function<void()>;
      using ClockStatusFunction = std::function<void(const Playback& status)>;
      using SongPositionFunction = std::function<void(const uint16_t& position)>;

   public:
      inline Parser();

   public:
      inline void prcocess(const Bytes& message);

      // register callback functions
      template <typename ClassType>
      void onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&, const Velocity&));

      template <typename ClassType>
      void onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&));

      template <typename ClassType>
      void onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uint8_t&));

      template <typename ClassType>
      void onClockTick(ClassType* instance, void (ClassType::*functionPointer)());

      template <typename ClassType>
      void onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&));

      template <typename ClassType>
      void onSongPosition(ClassType* instance, void (ClassType::*functionPointer)(const uint16_t&));

   protected:
      // default executes callback functions
      inline virtual void noteOn(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity);
      inline virtual void noteOff(const Channel& channel, const uint8_t& midiNote);
      inline virtual void controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value);
      inline virtual void clockTick();
      inline virtual void clockStatus(const Playback& status);
      inline virtual void songPosition(const uint16_t& position);

   private:
      std::vector<NoteOnFunction> noteOnFunctionList;
      std::vector<NoteOffFunction> noteOffFunctionList;
      std::vector<ControllerChangeFunction> controllerChangeFunctionList;
      std::vector<ClockTickFunction> clockTickFunctionList;
      std::vector<ClockStatusFunction> clockStatusFunctionList;
      std::vector<SongPositionFunction> songPositionFunctionList;
   };
} // namespace Midi

#ifndef MidiParserHPP
#include "../../MidiParser.hpp"
#endif // NOT MidiParserHPP

#endif // NOT MidiParserH
