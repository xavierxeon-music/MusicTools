#ifndef TimeCodeH
#define TimeCodeH

#include <limits>

#include <MusicTools.h>

class TimeCode
{
public:
   using Duration = uint16_t;
   static constexpr Duration maxDuration = std::numeric_limits<Duration>::max() - 1;

public:
   inline TimeCode();
   inline TimeCode(Duration bar, uint8_t quarter, uint8_t tick = 0);
   inline TimeCode(const Duration& duration);

public:
   inline std::string text() const;
   inline Duration toDuration() const;

public:
   Duration bar;
   uint8_t quarter;
   uint8_t tick;
};

#ifndef TimeCodeHPP
#include "../../TimeCode.hpp"
#endif // NOT TimeCodeHPP

#endif // NOT TimeCodeH
