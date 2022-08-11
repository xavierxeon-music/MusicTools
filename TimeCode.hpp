#ifndef TimeCodeHPP
#define TimeCodeHPP

#include <Music/TimeCode.h>

#include <Tools/Convert.h>

TimeCode::TimeCode()
   : bar(0)
   , quarter(0)
   , tick(0)
{
}

TimeCode::TimeCode(uint16_t bar, uint8_t quarter, uint8_t tick)
   : bar(bar)
   , quarter(quarter)
   , tick(tick)
{
}

TimeCode::TimeCode(const Duration& duration)
   : TimeCode()
{
   tick = duration % 4;
   quarter = ((duration - tick) / 4) % 4;

   const uint8_t restTicks = tick + (quarter * 4);
   const uint16_t barTicks = duration - restTicks;
   bar = barTicks / 16;
}

std::string TimeCode::text() const
{
   if (0 == toDuration())
      return "-- - -";

   const std::string frontText = Convert::text(bar);
   const std::string midText = Convert::text(quarter);
   const std::string backText = Convert::text(tick);

   const std::string durationText = frontText + " " + midText + " " + backText;
   return durationText;
}

TimeCode::Duration TimeCode::toDuration() const
{
   const Duration duration = (16 * bar) + (4 * quarter) + tick;
   return duration;
}

#endif // NOT TimeCodeHPP
