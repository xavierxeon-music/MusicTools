#ifndef TrackerSegmentHPP
#define TrackerSegmentHPP

#include <Tracker/TrackerSegment.h>

Tracker::Segment::Segment()
   : Remember::Container()
   , startValue(this, 0)
   , endValue(this, 0)
{
}

Tracker::Segment::Segment(const Segment& other)
   : Remember::Container()
   , startValue(this, other.startValue)
   , endValue(this, other.endValue)
{
}

uint8_t Tracker::Segment::getStartValue() const
{
   return startValue;
}

void Tracker::Segment::setStartValue(const uint8_t value)
{
   startValue = value;
   Remember::Root::setUnsynced();
}

uint8_t Tracker::Segment::getEndValue() const
{
   return endValue;
}

void Tracker::Segment::setEndValue(const uint8_t value)
{
   endValue = value;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerSegmentHPP
