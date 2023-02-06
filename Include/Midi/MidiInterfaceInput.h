#ifndef MidiInterfaceInputH
#define MidiInterfaceInputH

#include <Midi/MidiParser.h>

#include <functional>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

namespace Midi
{
   namespace Interface
   {
      class Output;

      class Input : public Parser
      {
      public:
         inline Input();
         inline virtual ~Input();

      public:
         inline virtual void open();
         inline virtual void close();
         inline virtual bool isOpen() const;

         inline void addPassThroughInterface(Interface::Output* passthrough);

      protected:
         std::vector<Interface::Output*> passthroughList;
      };
   } // namespace Interface
} // namespace Midi

#ifndef MidiInterfaceInputHPP
#include "../MidiInterfaceInput.hpp"
#endif // NOT MidiInterfaceInputHPP

#endif // NOT MidiInterfaceInputH
