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
   *this = other;
}

Tracker::Bank& Tracker::Bank::operator=(const Bank& other)
{
   segmentCount = other.segmentCount;
   for (uint8_t index = 0; index < 8; index++)
      tracks[index] = other.tracks[index];

   return *this;
}

void Tracker::Bank::init(const uint32_t newSegmentCount)
{
   segmentCount = newSegmentCount;

   for (uint8_t index = 0; index < 8; index++)
      tracks[index].resize(segmentCount);

   Remember::Root::setUnsynced();
}

Tracker::Track& Tracker::Bank::getTrack(const uint8_t trackIndex)
{
   return tracks[trackIndex];
}

#endif // NOT TrackerBankHPP
