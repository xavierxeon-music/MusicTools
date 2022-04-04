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
         using NoteOnFunction = std::function<void(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)>;
         using NoteOffFunction = std::function<void(const Midi::Channel& channel, const Note& note)>;
         using ControllChangeFunction = std::function<void(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)>;

      public:
         inline Input();
         inline virtual ~Input();

      public:
         inline virtual void open();
         inline virtual void close();

         template <typename ClassType>
         void onReceiveNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Midi::Velocity&));

         template <typename ClassType>
         void onReceiveNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&));

         template <typename ClassType>
         void onReceiveControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Midi::ControllerMessage&, const uint8_t&));

         inline void addPassThroughInterface(Interface::Output* passthrough);

      protected:
         inline void dataFromInput(const Bytes& message);

      protected:
         std::vector<NoteOnFunction> noteOnFunctionList;
         std::vector<NoteOffFunction> noteOffFunctionList;
         std::vector<ControllChangeFunction> controllChangeFunctionList;
         std::vector<Interface::Output*> passthroughList;
      };
   } // namespace Interface
} // namespace Midi

#ifndef MidiInterfaceInputHPP
#include "../MidiInterfaceInput.hpp"
#endif // NOT MidiInterfaceInputHPP

#endif // NOT MidiInterfaceInputH
