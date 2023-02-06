#ifndef MidiInterfaceInputHPP
#define MidiInterfaceInputHPP

#include <Midi/MidiInterfaceInput.h>

Midi::Interface::Input::Input()
   : Parser()
   , passthroughList()
{
}

Midi::Interface::Input::~Input()
{
   // do nothing
}

void Midi::Interface::Input::open()
{
   // do nothing
}

void Midi::Interface::Input::close()
{
   // do nothing
}

bool Midi::Interface::Input::isOpen() const
{
   return false;
}

void Midi::Interface::Input::addPassThroughInterface(Interface::Output* passthrough)
{
   passthroughList.push_back(passthrough);
}

#endif // NOT MidiInterfaceInputHPP
