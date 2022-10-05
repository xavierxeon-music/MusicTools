#ifndef FlankH
#define FlankH

#include <MusicTools.h>

pyexport class Flank
{
public:
   pyexport enum class State {
      Low,
      Rising,
      High,
      Falling
   };

public:
   pyexport inline Flank(const bool high = false);

public:
   pyexport inline State observe(const bool value);
   pyexport inline void reset(const bool high = false);

private:
   bool lastValue;
};

#ifndef FlankHPP
#include "../../Flank.hpp"
#endif // NOT FlankHPP

#endif // NOT FlankH
