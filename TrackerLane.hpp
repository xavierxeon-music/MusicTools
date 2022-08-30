#ifndef TrackerLaneHPP
#define TrackerLaneHPP

#include <Blocks/TrackerLane.h>

// segment

Tracker::Lane::Segment::Segment()
   : Remember::Container()
   , startValue(this, 0)
   , startExists(this, false)
   , endValue(this, 0)
   , endExists(this, false)
   , steady(this, false)
{
}

Tracker::Lane::Segment::Segment(const Segment& other)
   : Segment()
{
   *this = other;
}

Tracker::Lane::Segment& Tracker::Lane::Segment::operator=(const Segment& other)
{
   startValue = other.startValue;
   startExists = other.startExists;

   endValue = other.endValue;
   endExists = other.endExists;

   steady = other.steady;
   return *this;
}

// lane

Tracker::Lane::Lane()
   : Remember::Container()
   , name(this, "")
   , segments(this)
   , dirty(true)
   , proxyList()
{
}

Tracker::Lane::Lane(const Lane& other)
   : Lane()
{
   *this = other;
}

Tracker::Lane& Tracker::Lane::operator=(const Lane& other)
{
   const uint32_t segmentCount = other.segments.size();

   segments.clear();
   for (uint32_t index = 0; index < segmentCount; index++)
   {
      Segment segment = other.segments[index];
      segments.append(segment);
   }

   proxyList.resize(segmentCount);
   dirty = true;

   return *this;
}

void Tracker::Lane::resize(const uint32_t segmentCount)
{
   segments.clear();
   for (uint32_t index = 0; index < segmentCount; index++)
   {
      segments.append(Segment());
   }

   proxyList.resize(segmentCount);
   dirty = true;
   Remember::Root::setUnsynced();
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

uint8_t Tracker::Lane::getSegmentValue(const uint32_t index, const float& percentage) const
{
   if (dirty)
   {
      updateProxyList();
      dirty = false;
   }

   if (index >= segments.size())
      return 0;

   if (0.0 >= percentage)
      return proxyList[index].startValue;
   else if (1.0 <= percentage)
      return proxyList[index].endValue;

   // interpolate
   const float startValue = proxyList[index].startValue;
   const float diffValue = proxyList[index].endValue - proxyList[index].startValue;

   const float value = startValue + (percentage * diffValue);
   return static_cast<uint8_t>(value);
}

void Tracker::Lane::resetSegment(const uint32_t index)
{
   if (index >= segments.size())
      return;

   segments[index].startValue = 0;
   segments[index].startExists = false;

   segments[index].endValue = 0;
   segments[index].endExists = false;
}

uint8_t Tracker::Lane::getSegmentStartValue(const uint32_t index) const
{
   if (index >= segments.size())
      return 0;

   return segments[index].startValue;
}

bool Tracker::Lane::hasSegmentStartValue(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].startExists;
}

void Tracker::Lane::setSegmentStartValue(const uint32_t index, const uint8_t value)
{
   if (index >= segments.size())
      return;

   segments[index].startValue = value;
   segments[index].startExists = true;

   dirty = true;
   Remember::Root::setUnsynced();
}

uint8_t Tracker::Lane::getSegmentEndValue(const uint32_t index) const
{
   if (index >= segments.size())
      return 0;

   return segments[index].endValue;
}

bool Tracker::Lane::hasSegmentEndValue(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].endExists;
}

void Tracker::Lane::setSegmentEndValue(const uint32_t index, const uint8_t value)
{
   if (index >= segments.size())
      return;

   segments[index].endValue = value;
   segments[index].endExists = true;

   dirty = true;
   Remember::Root::setUnsynced();
}

bool Tracker::Lane::hasSegmentValues(const uint32_t index) const
{
   return segments[index].startExists || segments[index].endExists;
}

bool Tracker::Lane::isSegmentSteady(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].steady;
}

void Tracker::Lane::setSegmentSteady(const uint32_t index, bool on)
{
   if (index >= segments.size())
      return;

   segments[index].steady = on;

   dirty = true;
   Remember::Root::setUnsynced();
}

void Tracker::Lane::updateProxyList() const
{
   for (uint32_t index = 0; index < segments.size(); index++)
   {
      uint32_t startSegmentCount = 0;
      uint8_t startValue = segments[index].startValue;
      uint32_t startIndex = 0;
      for (startIndex = index; startIndex >= 0; startIndex--)
      {
         if (0 == startIndex && !segments[startIndex].startExists)
         {
            startValue = 0.0;
            break;
         }

         if (startIndex != index && segments[startIndex].endExists)
         {
            startValue = segments[startIndex].endValue;
            break;
         }

         if (segments[startIndex].startExists)
         {
            startValue = segments[startIndex].startValue;
            break;
         }

         startSegmentCount++;
      }

      uint32_t endSegmentCount = 0;
      uint8_t endValue = segments[index].endValue;
      for (uint32_t endIndex = index; endIndex < segments.size(); endIndex++)
      {
         if (endIndex + 1 == segments.size() && !segments[endIndex].endExists)
         {
            endValue = 0;
            break;
         }

         if (endIndex != index && segments[endIndex].startExists)
         {
            endValue = segments[endIndex].startValue;
            break;
         }

         if (segments[endIndex].endExists)
         {
            endValue = segments[endIndex].endValue;
            break;
         }

         endSegmentCount++;
      }

      bool startSteady = segments[startIndex].steady;
      if (startSteady)
      {
         proxyList[index].startValue = startValue;
         proxyList[index].endValue = startValue;
      }
      else
      {
         const float totalSegments = 1 + startSegmentCount + endSegmentCount;
         const float startPrecent = startSegmentCount / totalSegments;
         const float endPrecent = (startSegmentCount + 1) / totalSegments;

         const float start = startValue;
         const float diff = endValue - startValue;

         proxyList[index].startValue = static_cast<uint8_t>(start + (startPrecent * diff));
         proxyList[index].endValue = static_cast<uint8_t>(start + (endPrecent * diff));
      }
   }
}

#endif // NOT TrackerLaneHPP
