#ifndef ContourHPP
#define ContourHPP

#include <Blocks/Contour.h>

// segment

Contour::Segment::Segment()
   : Remember::Container()
   , startValue(this, 0)
   , startExists(this, false)
   , endValue(this, 0)
   , endExists(this, false)
   , steady(this, false)
{
}

Contour::Segment::Segment(const Segment& other)
   : Segment()
{
   *this = other;
}

Contour::Segment& Contour::Segment::operator=(const Segment& other)
{
   startValue = other.startValue;
   startExists = other.startExists;

   endValue = other.endValue;
   endExists = other.endExists;

   steady = other.steady;
   return *this;
}

// lane

Contour::Contour()
   : Remember::Container()
   , poly(nullptr)
   , name(this, "")
   , segments(this)
   , dirty(true)
   , proxyList()
{
}

Contour::Contour(const Contour& other)
   : Contour()
{
   *this = other;
}

Contour& Contour::operator=(const Contour& other)
{
   poly = other.poly;
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

void Contour::setup(Poly* poly)
{
   this->poly = poly;
}

void Contour::resize(const uint32_t segmentCount, bool clearContent)
{
   if (clearContent)
   {
      segments.clear();

      for (uint32_t index = 0; index < segmentCount; index++)
         segments.append(Segment());
   }
   else if (segments.size() < segmentCount)
   {
      for (uint32_t index = segments.size(); index < segmentCount; index++)
         segments.append(Segment());
   }
   else
   {
      while (segments.size() > segmentCount)
         segments.remove(segments.size() - 1);
   }

   proxyList.resize(segmentCount);
   dirty = true;
   Remember::Root::setUnsynced();
}

std::string Contour::getName() const
{
   return name;
}

void Contour::setName(const std::string& text)
{
   name = text;
   Remember::Root::setUnsynced();
}

uint8_t Contour::getSegmentValue(const uint32_t index, const float& segmentPercentage) const
{
   if (dirty)
   {
      updateProxyList();
      dirty = false;
   }

   if (index >= segments.size())
      return 0;

   if (0.0 >= segmentPercentage)
      return proxyList[index].startValue;
   else if (1.0 <= segmentPercentage)
      return proxyList[index].endValue;

   // interpolate
   const float startValue = proxyList[index].startValue;
   const float diffValue = proxyList[index].endValue - proxyList[index].startValue;

   const float value = startValue + (segmentPercentage * diffValue);
   return static_cast<uint8_t>(value);
}

void Contour::resetSegment(const uint32_t index)
{
   if (index >= segments.size())
      return;

   segments[index].startValue = 0;
   segments[index].startExists = false;

   segments[index].endValue = 0;
   segments[index].endExists = false;
}

uint8_t Contour::getSegmentStartValue(const uint32_t index) const
{
   if (index >= segments.size())
      return 0;

   return segments[index].startValue;
}

bool Contour::hasSegmentStartValue(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].startExists;
}

void Contour::setSegmentStartValue(const uint32_t index, const uint8_t value)
{
   if (index >= segments.size())
      return;

   segments[index].startValue = value;
   segments[index].startExists = true;

   dirty = true;
   Remember::Root::setUnsynced();
}

uint8_t Contour::getSegmentEndValue(const uint32_t index) const
{
   if (index >= segments.size())
      return 0;

   return segments[index].endValue;
}

bool Contour::hasSegmentEndValue(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].endExists;
}

void Contour::setSegmentEndValue(const uint32_t index, const uint8_t value)
{
   if (index >= segments.size())
      return;

   segments[index].endValue = value;
   segments[index].endExists = true;

   dirty = true;
   Remember::Root::setUnsynced();
}

bool Contour::hasSegmentValues(const uint32_t index) const
{
   return segments[index].startExists || segments[index].endExists;
}

bool Contour::isSegmentSteady(const uint32_t index) const
{
   if (index >= segments.size())
      return false;

   return segments[index].steady;
}

void Contour::setSegmentSteady(const uint32_t index, bool on)
{
   if (index >= segments.size())
      return;

   segments[index].steady = on;

   dirty = true;
   Remember::Root::setUnsynced();
}

void Contour::updateProxyList() const
{
   for (uint32_t index = 0; index < segments.size(); index++)
   {
      uint32_t startSegmentCount = 0;
      uint8_t startValue = segments[index].startValue;

      uint32_t startIndex = index;
      while (true)
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
         startIndex--;
      }

      uint32_t endSegmentCount = 0;
      uint8_t endValue = segments[index].endValue;
      for (uint32_t endIndex = index; endIndex < segments.size(); endIndex++)
      {
         if (endIndex != index && segments[endIndex].startExists)
         {
            endValue = segments[endIndex].startValue;
            endSegmentCount--;
            break;
         }

         if (segments[endIndex].endExists)
         {
            endValue = segments[endIndex].endValue;
            break;
         }

         if (endIndex + 1 == segments.size() && !segments[endIndex].endExists)
         {
            endValue = 0;
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
// project

Contour::Poly::Poly()
   : Abstract::SegmentCrawler()
   , contours(this)
{
   for (uint8_t contourIndex = 0; contourIndex < getContourCount(); contourIndex++)
      contours[contourIndex].setup(this);
}

void Contour::Poly::clear()
{
   Abstract::SegmentCrawler::clear();

   for (uint8_t contourIndex = 0; contourIndex < getContourCount(); contourIndex++)
      contours[contourIndex].resize(0, true);
}

void Contour::Poly::update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);

   for (uint8_t contourIndex = 0; contourIndex < getContourCount(); contourIndex++)
      contours[contourIndex].resize(getSegmentCount(), false);
}

uint8_t Contour::Poly::getContourCount() const
{
   return contourCount;
}

Contour& Contour::Poly::getContour(const uint8_t contourIndex)
{
   return contours[contourIndex];
}

const Contour& Contour::Poly::getConstContour(const uint8_t contourIndex) const
{
   return contours[contourIndex];
}

#endif // NOT ContourHPP
