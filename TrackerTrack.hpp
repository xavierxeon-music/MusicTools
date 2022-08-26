#ifndef TrackerTrackHPP
#define TrackerTrackHPP

#include <Tracker/TrackerTrack.h>

Tracker::Track::Track()
   : Remember::Container()
   , name(this, "")
   , type(this, Type::CV)
   , steady(this, false)
   , segments(this)
{
}

Tracker::Track& Tracker::Track::operator=(const Track& other)
{
   return *this;
}

void Tracker::Track::resize(const uint32_t segementCount)
{
   segments.clear();
   for (uint32_t index = 0; index < segementCount; index++)
   {
      segments.append(Segment());
   }
}

Tracker::Segment& Tracker::Track::getSegment(const uint32_t index)
{
   return segments[index];
}

#endif // NOT TrackerTrackHPP
