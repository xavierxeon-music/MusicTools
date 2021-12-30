#ifndef GateOscilatorHPP
#define GateOscilatorHPP

#include <Sound/GateOscilator.h>

GateOscilator::GateOscilator()
   : Abstract::Oscilator()
   , isOn(false)
   , square(8, true)
{
}

float GateOscilator::createSound()
{
   const bool high = square.valueAndNext();

   if (!isOn)
      return 0.0;
   else if (high)
      return 1.0;
   else
      return -1.0;
}

void GateOscilator::setOn(bool on)
{
   isOn = on;
}

#endif // GateOscilatorHPP
