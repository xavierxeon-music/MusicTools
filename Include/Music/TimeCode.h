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
   TimeCode();
   TimeCode(Duration bar, uint8_t quarter, uint8_t tick = 0);
   TimeCode(const Duration& duration);

public:
   std::string text() const;
   Duration toDuration() const;

public:
   Duration bar;
   uint8_t quarter;
   uint8_t tick;
};

#ifndef TimeCodeHPP
#include "../../TimeCode.hpp"
#endif // NOT TimeCodeHPP

#endif // NOT TimeCodeH
