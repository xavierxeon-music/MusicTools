#ifndef ContoursHPP
#define ContoursHPP

#include <Blocks/Contours.h>

// segment

Contours::Segment::Segment()
   : store(0)
{
}

Contours::Segment::Segment(const Segment& other)
   : store(other.store)
{
}

Contours::Segment& Contours::Segment::operator=(const Segment& other)
{
   store = other.store;

   return *this;
}

void Contours::Segment::setStartValue(const uint8_t value)
{
   startValue = value;
   hasStartValue = 1;
}

void Contours::Segment::setEndValue(const uint8_t value)
{
   endValue = value;
   hasEndValue = 1;
}

// contours

Contours::Contours()
   : Abstract::SegmentCrawler()
   , lanes{}
   , zeroSegment()
{
}

void Contours::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);
}

void Contours::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);
}

const std::string& Contours::getName(const uint8_t laneIndex) const
{
   return lanes[laneIndex].name;
}

void Contours::setName(const uint8_t laneIndex, const std::string& text)
{
   lanes[laneIndex].name = text;
}

uint8_t Contours::getSegmentValue(const uint8_t laneIndex, const uint32_t segmentIndex, const float& segmentPercentage) const
{
   const Proxy& proxy = lanes[laneIndex].proxyList.at(segmentIndex);
   const uint8_t startValue = proxy.startValue;
   const double diff = (proxy.endValue - startValue);

   const uint8_t value = startValue + (segmentPercentage * diff);

   return value;
}

const Contours::Segment& Contours::getSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   const Segment& segment = lanes[laneIndex].segmentMap.at(segmentIndex);
   return segment;
}

bool Contours::hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   if (lanes[laneIndex].segmentMap.find(segmentIndex) == lanes[laneIndex].segmentMap.end())
      return false;

   return true;
}

void Contours::setSegment(const uint8_t laneIndex, const uint32_t segmentIndex, const Segment& segment)
{
   lanes[laneIndex].segmentMap[segmentIndex] = segment;
   updateProxies();
}

void Contours::clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex)
{
   lanes[laneIndex].segmentMap.erase(segmentIndex);
   updateProxies();
}

void Contours::updateProxies()
{
   for (uint8_t laneIndex = 0; laneIndex < laneCount; laneIndex++)
   {
      const SegmentMap& segmentMap = lanes[laneIndex].segmentMap;
      Proxy::List& proxyList = lanes[laneIndex].proxyList;

      proxyList.clear();
      proxyList.resize(getSegmentCount());

      // first and last proxy
      proxyList[0].hasStartValue = true;
      proxyList[getSegmentCount() - 1].hasEndValue = true;

      // fill proxy
      uint32_t rampStartIndex = 0;
      for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
      {
         if (!hasSegment(laneIndex, segmentIndex))
         {
            proxyList[segmentIndex].rampStartIndex = rampStartIndex;
            continue;
         }

         rampStartIndex = segmentIndex;
         proxyList[segmentIndex].rampStartIndex = rampStartIndex;

         const Segment& segment = segmentMap.at(segmentIndex);

         proxyList[segmentIndex].startValue = segment.startValue;
         proxyList[segmentIndex].hasStartValue = (1 == segment.hasStartValue);

         proxyList[segmentIndex].endValue = segment.endValue;
         proxyList[segmentIndex].hasEndValue = (1 == segment.hasEndValue);
      }

      // propagate end values
      for (uint32_t segmentIndex = 1; segmentIndex < getSegmentCount(); segmentIndex++)
      {
         if (proxyList[segmentIndex].hasStartValue && !proxyList[segmentIndex - 1].hasEndValue)
         {
            proxyList[segmentIndex - 1].endValue = proxyList[segmentIndex].startValue;
            proxyList[segmentIndex - 1].hasEndValue = true;
         }
      }

      // interpolate
      for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
      {
         if (!proxyList[segmentIndex].hasEndValue)
         {
            const uint8_t startValue = proxyList[segmentIndex].startValue;
            uint8_t endValue = 0;

            uint32_t segmentIndex2 = segmentIndex;
            for (; segmentIndex2 < getSegmentCount(); segmentIndex2++)
            {
               if (!proxyList[segmentIndex2].hasEndValue)
                  continue;
               endValue = proxyList[segmentIndex2].endValue;
               break;
            }

            const double length = 1 + (segmentIndex2 - segmentIndex);
            const double slope = (endValue - startValue) / length;
            for (uint32_t segmentIndex3 = segmentIndex; segmentIndex3 <= segmentIndex2; segmentIndex3++)
            {
               if (!proxyList[segmentIndex3].hasStartValue)
               {
                  proxyList[segmentIndex3].startValue = startValue + (slope * (segmentIndex3 - segmentIndex));
                  proxyList[segmentIndex3].hasStartValue = true;
               }
               if (!proxyList[segmentIndex3].hasEndValue)
               {
                  proxyList[segmentIndex3].endValue = startValue + (slope * (1 + segmentIndex3 - segmentIndex));
                  proxyList[segmentIndex3].hasEndValue = true;
               }
            }
         }
      }
   }
}

#endif // NOT ContoursHPP
