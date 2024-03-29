#ifndef TimeCodeHPP
#define TimeCodeHPP

#include <Music/TimeCode.h>

#include <Tools/Text.h>

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
   const std::string frontText = Text::convert(bar + 1);
   const std::string midText = Text::convert(quarter + 1);
   const std::string backText = Text::convert(tick + 1);

   const std::string durationText = frontText + " " + midText + " " + backText;
   return durationText;
}

TimeCode::Duration TimeCode::toDuration() const
{
   const Duration duration = (16 * bar) + (4 * quarter) + tick;
   return duration;
}

#endif // NOT TimeCodeHPP
