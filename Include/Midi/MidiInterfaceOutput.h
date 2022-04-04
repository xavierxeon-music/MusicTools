#ifndef MidiInterfaceOutputH
#define MidiInterfaceOutputH

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

namespace Midi
{
   namespace Interface
   {
      class Output
      {
      public:
         inline Output();
         inline virtual ~Output();

      public:
         inline virtual void open();
         inline virtual void close();

         inline void sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity);
         inline void sendNoteOff(const Midi::Channel& channel, const Note& note);
         inline void sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value);

         virtual void sendBuffer(const Bytes& message) = 0;
      };
   } // namespace Interface
} // namespace Midi

#ifndef MidiInterfaceOutputHPP
#include "../MidiInterfaceOutput.hpp"
#endif // NOT MidiInterfaceOutputHPP

#endif // NOT MidiInterfaceOutputH
