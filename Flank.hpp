#ifndef FlankHPP
#define FlankHPP

#include <Tools/Flank.h>

Flank::Flank(const bool high)
   : lastValue(high)
{
}

Flank::State Flank::observe(const bool value)
{
   if (value && lastValue)
   {
      return State::High;
   }
   else if (!value && !lastValue)
   {
      return State::Low;
   }
   else if (value && !lastValue)
   {
      lastValue = value;
      return State::Falling;
   }

   lastValue = value;
   return State::Rising;
}

void Flank::reset(const bool high)
{
   lastValue = high;
}

#endif // NOT FlankHPP
