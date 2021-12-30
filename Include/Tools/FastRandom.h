#ifndef FastRandomH
#define FastRandomH

#include <limits>

#include <MusicTools.h>

// do not use system implementation,
// so that we can have several generators with independent seeds

// A linear congruential generator
class FastRandom
{
public:
   inline FastRandom(const uint64_t& seed = 0);

public:
   inline void reset(const uint64_t& seed = 0);
   inline void skip(const uint64_t& noOfValues);
   inline float value();

private:
   uint64_t current;
   // see https://en.wikipedia.org/wiki/Linear_congruential_generator
   static const uint64_t a = 1664525;
   static const uint64_t c = 1013904223;

   // no typo: max is half the byte size
   static const uint64_t max = std::numeric_limits<uint32_t>::max();
};

#include <FastRandom.hpp>

#endif // FastRandomH
