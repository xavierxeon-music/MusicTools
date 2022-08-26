#ifndef TrackerBankHPP
#define TrackerBankHPP

#include <Tracker/TrackerBank.h>

Tracker::Bank::Bank()
   : Remember::Container()
   , tracks(this)
   , segmentCount(0)
{
}

Tracker::Bank::Bank(const Bank& other)
   : Bank()
{
   for (uint8_t index = 0; index < 8; index++)
      tracks[index] = other.tracks[index];
}

void Tracker::Bank::init(const uint32_t newSegmentCount)
{
   segmentCount = newSegmentCount;

   for (uint8_t index = 0; index < 8; index++)
      tracks[index].resize(segmentCount);
}

#endif // NOT TrackerBankHPP
