#ifndef GlideHPP
#define GlideHPP

#include <Tools/Glide.h>

Glide::Glide()
   : maxSteps(1)
   , stepsLeft(maxSteps)
   , targetValue(0.0)
   , currentValue(0.0)
{
}

void Glide::setTarget(const float& newTarget, const size_t& maxSteps)
{
   targetValue = newTarget;
   stepsLeft = maxSteps;
}

const float& Glide::next()
{
   if (1 == stepsLeft)
   {
      currentValue = targetValue;
      stepsLeft = 0;
   }
   else if (1 < stepsLeft)
   {
      const float diff = (targetValue - currentValue) / stepsLeft;
      currentValue += diff;
      stepsLeft--;
   }

   return currentValue;
}

#endif //  GlideHPP
