#ifndef GlideH
#define GlideH

class Glide
{
public:
   inline Glide();

public:
   inline void setTarget(const float& newTarget, const size_t& maxSteps);
   inline const float& next();

private:
   size_t maxSteps;
   size_t stepsLeft;
   float targetValue;
   float currentValue;
};

#include <Glide.hpp>

#endif // GlideH
