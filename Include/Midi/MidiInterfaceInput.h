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
         using ControllerChangeFunction = std::function<void(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)>;
         using ClockTickFunction = std::function<void()>;
         using ClockStatusFunction = std::function<void(const Playback& status)>;

      public:
         inline Input();
         inline virtual ~Input();

      public:
         inline virtual void open();
         inline virtual void close();
         inline virtual bool isOpen() const;

         template <typename ClassType>
         void onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&, const Velocity&));
         inline virtual void noteOn(const Channel& channel, const Note& note, const Velocity& velocity);

         template <typename ClassType>
         void onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const Note&));
         inline virtual void noteOff(const Channel& channel, const Note& note);

         template <typename ClassType>
         void onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uint8_t&));
         inline virtual void controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value);

         template <typename ClassType>
         void onClockTick(ClassType* instance, void (ClassType::*functionPointer)());
         inline virtual void clockTick();

         template <typename ClassType>
         void onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&));
         inline virtual void clockStatus(const Playback& status);

         inline void addPassThroughInterface(Interface::Output* passthrough);

      protected:
         inline virtual void dataFromInput(const Bytes& message);

      protected:
         std::vector<NoteOnFunction> noteOnFunctionList;
         std::vector<NoteOffFunction> noteOffFunctionList;
         std::vector<ControllerChangeFunction> controllerChangeFunctionList;
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
