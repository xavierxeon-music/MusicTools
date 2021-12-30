#ifndef CounterHPP
#define CounterHPP

#include <Tools/Counter.h>

Counter::Counter(const uint64_t& maxValue)
   : maxValue(maxValue)
   , currentValue(0)
{
}

void Counter::reset()
{
   currentValue = 0;
}

void Counter::setMaxValue(const uint64_t& newMaxValue)
{
   maxValue = newMaxValue;
   currentValue = 0;
}

uint64_t Counter::valueAndNext()
{
   const uint64_t value = currentValue;

   currentValue++;
   if (maxValue == currentValue)
      currentValue = 0;

   return value;
}

const uint64_t& Counter::getCurrentValue() const
{
   return currentValue;
}

bool Counter::nextAndIsMaxValue()
{
   currentValue++;
   if (maxValue == currentValue)
   {
      currentValue = 0;
      return true;
   }
   return false;
}

const uint64_t& Counter::getMaxValue() const
{
   return maxValue;
}

#endif // CounterHPP
