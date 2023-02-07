#include <Midi/MidiCommon.h>

const float Midi::Variables::msPerByte = 1000.0f / 3125.0f; // -> 3125 bytes per second

bool Midi::isEvent(const uint8_t value, const Midi::Event mask)
{
   const bool isSystemEvent = (0xf0 == (value & 0xf0));

   if (isSystemEvent)
      return (mask == (mask & value));
   else
      return (mask == (value & 0xf0));
}

bool Midi::hasFirstBit(const uint8_t value)
{
   static const uint8_t checkMask = 0x80; // bit 7 only

   bool test = ((value & checkMask) == checkMask);
   return test;
}

uint8_t Midi::removeFirstBit(const uint8_t value)
{
   static const uint8_t valueMask = 0x7f; // all but bit 7

   return (value & valueMask);
}
