#ifndef GateOscilatorHPP
#define GateOscilatorHPP

#include <Sound/GateOscilator.h>

GateOscilator::GateOscilator()
   : Abstract::Oscilator()
   , isOn(false)
   , square(8, true)
   , minValue(-1.0)
   , maxValue(1.0)
{
}

float GateOscilator::createSound()
{
   const bool high = square.valueAndNext();

   if (!isOn)
      return 0.0;
   else if (high)
      return maxValue;
   else
      return minValue;
}

void GateOscilator::setOn(bool on)
{
   isOn = on;
}

void GateOscilator::setMinValue(const float& value)
{
   minValue = value;
}

void GateOscilator::setMaxValue(const float& value)
{
   maxValue = value;
}

#endif // GateOscilatorHPP
