#ifndef TimeCodeH
#define TimeCodeH

#include <limits>

#include <MusicTools.h>

pyexport class TimeCode
{
public:
   using Duration = uint16_t;
   static constexpr Duration maxDuration = std::numeric_limits<Duration>::max() - 1;

public:
   inline TimeCode();
   pyexport inline TimeCode(uint16_t bar, uint8_t quarter, uint8_t tick = 0);
   inline TimeCode(const Duration& duration);

public:
   pyexport inline std::string text() const;
   pyexport inline Duration toDuration() const;

public:
   pyexport uint16_t bar;
   pyexport uint8_t quarter;
   pyexport uint8_t tick;
};

#ifndef TimeCodeHPP
#include "../../TimeCode.hpp"
#endif // NOT TimeCodeHPP

#endif // NOT TimeCodeH
