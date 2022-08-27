#ifndef TrackerLaneHPP
#define TrackerLaneHPP

#include <Tracker/TrackerLane.h>

Tracker::Lane::Lane()
   : Remember::Container()
   , name(this, "")
   , type(this, Type::CV)
   , steady(this, false)
   , segments(this)
{
}

Tracker::Lane::Lane(const Lane& other)
   : Lane()
{
   *this = other;
}

Tracker::Lane& Tracker::Lane::operator=(const Lane& other)
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

void Tracker::Lane::resize(const uint32_t segementCount)
{
   segments.clear();
   for (uint32_t index = 0; index < segementCount; index++)
   {
      segments.append(Segment());
   }
   Remember::Root::setUnsynced();
}

Tracker::Segment& Tracker::Lane::getSegment(const uint32_t index)
{
   return segments[index];
}

std::string Tracker::Lane::getName() const
{
   return name;
}

void Tracker::Lane::setName(const std::string& text)
{
   name = text;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerLaneHPP
