#ifndef MidiInterfaceH
#define MidiInterfaceH

#include <functional>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

namespace Midi
{
   class Interface
   {
   public:
      using NoteOnFunction = std::function<void(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)>;
      using NoteOffFunction = std::function<void(const Midi::Channel& channel, const Note& note)>;
      using ControllChangeFunction = std::function<void(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)>;

   public:
      inline Interface();
      inline virtual ~Interface();

   public:
      inline virtual void initMidi(bool verbose = false);

      inline void sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity);
      inline void sendNoteOff(const Midi::Channel& channel, const Note& note);
      inline void sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value);

      virtual void sendBuffer(const Bytes& buffer) = 0;

      template <typename ClassType>
      void onReceiveNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&, const Midi::Velocity&));

      template <typename ClassType>
      void onReceiveNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Note&));

      template <typename ClassType>
      void onReceiveControllChange(ClassType* instance, void (ClassType::*functionPointer)(const Midi::Channel&, const Midi::ControllerMessage&, const uint8_t&));

      inline void addPassThroughInterface(Interface* passthrough);

   protected:
      std::vector<NoteOnFunction> noteOnFunctionList;
      std::vector<NoteOffFunction> noteOffFunctionList;
      std::vector<ControllChangeFunction> controllChangeFunctionList;
      std::vector<Interface*> passthroughList;
   };
} // namespace Midi

#ifndef MidiInterfaceHPP
#include "../MidiInterface.hpp"
#endif // NOT MidiInterfaceHPP

#endif // NOT MidiInterfaceH
