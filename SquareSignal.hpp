#ifndef SquareSignalHPP
#define SquareSignalHPP

#include <Utility/SquareSignal.h>

SquareSignal::SquareSignal(const uint8_t& halfLength, const bool& startHigh)
   : halfLength(halfLength)
   , startHigh(startHigh)
   , counter(0)
   , state(startHigh)
{
}

bool SquareSignal::value() const
{
   return state;
}

bool SquareSignal::valueAndNext()
{
   bool current = state;

   counter++;
   if (counter == halfLength)
   {
      counter = 0;
      state = !state;
   }

   return current;
}

void SquareSignal::reset()
{
   counter = 0;
   state = startHigh;
}

#endif // SquareSignalHPP
