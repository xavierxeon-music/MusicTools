#ifndef TrackerSegmentHPP
#define TrackerSegmentHPP

#include <Tracker/TrackerSegment.h>

Tracker::Segment::Segment()
   : Remember::Container()
   , startValue(this, 0)
   , startExists(this, false)
   , endValue(this, 0)
   , endExists(this, false)
   , steady(this, false)
{
}

Tracker::Segment::Segment(const Segment& other)
   : Remember::Container()
   , startValue(this, other.startValue)
   , startExists(this, other.startExists)
   , endValue(this, other.endValue)
   , endExists(this, other.endExists)
   , steady(this, other.steady)
{
}

void Tracker::Segment::reset()
{
   startValue = 0;
   startExists = false;

   endValue = 0;
   endExists = false;
}

uint8_t Tracker::Segment::getStartValue() const
{
   return startValue;
}

bool Tracker::Segment::hasStartValue() const
{
   return startExists;
}

void Tracker::Segment::setStartValue(const uint8_t value)
{
   startValue = value;
   startExists = true;
   Remember::Root::setUnsynced();
}

uint8_t Tracker::Segment::getEndValue() const
{
   return endValue;
}

bool Tracker::Segment::hasEndValue() const
{
   return endExists;
}

void Tracker::Segment::setEndValue(const uint8_t value)
{
   endValue = value;
   endExists = true;
   Remember::Root::setUnsynced();
}

bool Tracker::Segment::hasValues() const
{
   return startExists || endExists;
}

bool Tracker::Segment::isSteady() const
{
   return steady;
}

void Tracker::Segment::setSteady(bool on)
{
   steady = on;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerSegmentHPP
