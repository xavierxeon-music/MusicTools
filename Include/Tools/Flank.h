#ifndef FlankH
#define FlankH

#include <MusicTools.h>

class Flank
{
public:
   enum class State {
      Low,
      Rising,
      High,
      Falling
   };

public:
   inline Flank(const bool high = false);

public:
   inline State observe(const bool value);
   inline void reset(const bool high = false);

private:
   bool lastValue;
};

#ifndef FlankHPP
#include "../../Flank.hpp"
#endif // NOT FlankHPP

#endif // NOT FlankH
