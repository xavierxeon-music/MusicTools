#ifndef MidiTargetDoepferQuadH
#define MidiTargetDoepferQuadH

#include <Midi/MidiInterfaceOutput.h>
#include <Music/Note.h>

#include <Tools/Range.h>

namespace Midi
{
   namespace Target
   {

      // set to quad mono mode
      class DoepferQuad
      {
      public:
         // a strip has 3 cv outputs, corresponding to pitch, cv2 and cv3
         // when cv2 (velocity) is set to 0, then cv1 (pitch) will also be zero!
         // uses default channels 1-4
         class Strip
         {
         public:
            inline Strip();

         public:
            inline void setCV12(float voltage1, float voltage2 = 5.0); // voltages between 0.0V and 5.0V
            inline void setCV3(float voltage3);                        // voltages between 0.0V and 5.0V
         private:
            inline Strip(Interface::Output* midiOutput, const Channel& midiChannel, const ControllerMessage& controllerMessage, const uint8_t refNote);

         private:
            friend class DoepferQuad;

         private:
            Interface::Output* midiOutput;
            Channel midiChannel;
            ControllerMessage controllerMessage;
            int8_t noteDiff;
            Note prevNote;

            inline static const Range::Mapper mapper = Range::Mapper(0.0, 5.0, 0.0, 127.0);
         };

      public:
         inline DoepferQuad(Interface::Output* midiOutput);

      public:
         // for each strip set cv3 config to controllerMessage (default is 102). cv2 is kept at velocity
         inline Strip create(const Channel& midiChannel, const ControllerMessage& controllerMessage = ControllerMessage::User01, const uint8_t refNote = 24);

      private:
         Interface::Output* midiOutput;
      };
   } // namespace Target
} // namespace Midi

#ifndef MidiTargetDoepferQuadHPP
#include "../MidiTargetDoepferQuad.hpp"
#endif // NOT MidiTargetDoepferQuadHPP

#endif // NOT MidiTargetDoepferQuadH
