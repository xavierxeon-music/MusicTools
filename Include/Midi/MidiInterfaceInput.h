#ifndef MidiInterfaceInputH
#define MidiInterfaceInputH

#include <functional>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

namespace Midi
{
   namespace Interface
   {
      class Output;

      class Input
      {
      public:
         using NoteOnFunction = std::function<void(const Channel& channel, const Note& note, const Velocity& velocity)>;
         using NoteOffFunction = std::function<void(const Channel& channel, const Note& note)>;
         using ControllChangeFunction = std::function<void(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)>;
         using ClockTickFunction = std::function<void()>;
         using ClockStatusFunction = std::function<void(const Playback& status)>;

      public:
         inline Input();
         inline virtual ~Input();

      public:
         inline virtual void open();
         inline virtual void close();

         template <typename ClassType>
         void onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&, const Velocity&));

         template <typename ClassType>
         void onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&));

         template <typename ClassType>
         void onControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uint8_t&));

         template <typename ClassType>
         void onClockTick(ClassType* instance, void (ClassType::*functionPointer)());

         template <typename ClassType>
         void onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&));

         inline void addPassThroughInterface(Interface::Output* passthrough);

      protected:
         inline void dataFromInput(const Bytes& message);

      protected:
         std::vector<NoteOnFunction> noteOnFunctionList;
         std::vector<NoteOffFunction> noteOffFunctionList;
         std::vector<ControllChangeFunction> controllChangeFunctionList;
         std::vector<ClockTickFunction> clockTickFunctionList;
         std::vector<ClockStatusFunction> clockStatusFunctionList;
         std::vector<Interface::Output*> passthroughList;
      };
   } // namespace Interface
} // namespace Midi

#ifndef MidiInterfaceInputHPP
#include "../MidiInterfaceInput.hpp"
#endif // NOT MidiInterfaceInputHPP

#endif // NOT MidiInterfaceInputH
