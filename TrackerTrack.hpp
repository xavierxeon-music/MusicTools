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

Tracker::Track::Track(const Track& other)
   : Track()
{
   *this = other;
}

Tracker::Track& Tracker::Track::operator=(const Track& other)
{
   const uint32_t segementCount = other.segments.size();

   segments.clear();
   for (uint32_t index = 0; index < segementCount; index++)
   {
      Segment segment = other.segments[index];
      segments.append(segment);
   }

   return *this;
}

void Tracker::Track::resize(const uint32_t segementCount)
{
   segments.clear();
   for (uint32_t index = 0; index < segementCount; index++)
   {
      segments.append(Segment());
   }
   Remember::Root::setUnsynced();
}

Tracker::Segment& Tracker::Track::getSegment(const uint32_t index)
{
   return segments[index];
}

std::string Tracker::Track::getName() const
{
   return name;
}

void Tracker::Track::setName(const std::string& text)
{
   name = text;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerTrackHPP
