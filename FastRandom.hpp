#ifndef FastRandomHPP
#define FastRandomHPP

#include <Tools/FastRandom.h>

#ifdef NON_DAISY_DEVICE
#include <ctime>
#endif

#include <MusicTools.h>

FastRandom::FastRandom(const uint64_t& seed)
   : current(seed)
{
#ifdef NON_DAISY_DEVICE
   static bool doneOnce = false;
   if (!doneOnce)
   {
      srand(time(0));
      doneOnce = true;
   }
#endif
}

void FastRandom::reset(const uint64_t& seed)
{
   current = seed;
}

void FastRandom::skip(const uint64_t& noOfValues)
{
   for (uint64_t index = 0; index < noOfValues; index++)
      value();
}

float FastRandom::value()
{
   static const float fMax = static_cast<float>(max);

   current = (a * current + c) % max;
   const float fValue = static_cast<float>(current) / fMax;
   return fValue;
}

#endif // FastRandomHPP
