#ifndef MidiDeviceDoepferQuadH
#define MidiDeviceDoepferQuadH

#include <Midi/MidiInterface.h>
#include <Music/Note.h>

namespace Midi
{
   namespace Device
   {

      // set to quad mono mode
      class DoepferQuad
      {
      public:
         // a strip has 3 cv, corresponding to pitch, cv2 and cv3
         class Strip
         {
         public:
            inline Strip();

         public:
            inline void setCV(uint8_t output, float voltage); // output 0-2, voltage between 0.0V and 5.0V
         private:
            inline Strip(Midi::Interface* midiInterface, const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage);

         private:
            friend class DoepferQuad;

         private:
            Midi::Interface* midiInterface;
            Channel midiChannel;
            Midi::ControllerMessage controllerMessage;
            Note note;
            Midi::Velocity velocity;
            uint8_t controllerValue;
         };

      public:
         inline DoepferQuad(Midi::Interface* midiInterface);

      public:
         // for user01 set cv3 to 102, cv2 is kept at velocity
         inline Strip create(const Channel& midiChannel, const Midi::ControllerMessage& controllerMessage = Midi::ControllerMessage::User01);

      private:
         Midi::Interface* midiInterface;
      };
   } // namespace Device
} // namespace Midi

#ifndef MidiDeviceDoepferQuadHPP
#include "../MidiDeviceDoepferQuad.hpp"
#endif // NOT MidiDeviceDoepferQuadHPP

#endif // NOT MidiDeviceDoepferQuadH
