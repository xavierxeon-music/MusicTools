#ifndef ContoursHPP
#define ContoursHPP

#include <Blocks/Contours.h>

// segment

Contours::Segment::Segment()
   : value(0)
{
}

Contours::Segment::Segment(const Segment& other)
   : value(other.value)
{
}

Contours::Segment& Contours::Segment::operator=(const Segment& other)
{
   value = other.value;

   return *this;
}

bool Contours::Segment::hasStartValue() const
{
   const bool test = (0 != (flags & HasStartValue));
   return test;
}

bool Contours::Segment::hasEndValue() const
{
   const bool test = (0 != (flags & HasEndValue));
   return test;
}

bool Contours::Segment::isSteady() const
{
   return (1 == steady);
}

void Contours::Segment::setStartValue(const uint8_t value)
{
   startValue = value;
   flags |= HasStartValue;
}

void Contours::Segment::setEndValue(const uint8_t value)
{
   endValue = value;
   flags |= HasEndValue;
}

void Contours::Segment::setSteady(bool steady)
{
   this->steady = steady ? 1 : 0;
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

      // first proxy
      proxyList[0].hasStartValue = true;
      proxyList[0].isSteady = true;

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
         proxyList[segmentIndex].hasStartValue = segment.hasStartValue();

         proxyList[segmentIndex].endValue = segment.endValue;
         proxyList[segmentIndex].hasEndValue = segment.hasEndValue();

         proxyList[segmentIndex].isSteady = segment.isSteady();
      }

      // propagate
      for (uint32_t segmentIndex = 1; segmentIndex < getSegmentCount(); segmentIndex++)
      {
         if (proxyList[segmentIndex - 1].isSteady && !proxyList[segmentIndex].hasStartValue && !proxyList[segmentIndex].hasEndValue)
         {
            proxyList[segmentIndex].startValue = proxyList[segmentIndex - 1].startValue;
            proxyList[segmentIndex].hasStartValue = true;

            proxyList[segmentIndex].endValue = proxyList[segmentIndex].startValue;
            proxyList[segmentIndex].hasEndValue = true;

            proxyList[segmentIndex].isSteady = true;
         }

         if (proxyList[segmentIndex].hasStartValue && !proxyList[segmentIndex - 1].hasEndValue && !proxyList[segmentIndex - 1].isSteady)
         {
            proxyList[segmentIndex - 1].endValue = proxyList[segmentIndex].startValue;
            proxyList[segmentIndex - 1].hasEndValue = true;
         }

         if (getSegmentCount() == segmentIndex + 1 && !proxyList[segmentIndex].hasEndValue)
         {
            if (proxyList[segmentIndex].isSteady)
            {
               proxyList[segmentIndex].endValue = proxyList[segmentIndex].startValue;
            }
            proxyList[segmentIndex].hasEndValue = true;
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

         /*
         if (0 == laneIndex)
         {
            QDebug dbg = qDebug();
            dbg << laneIndex << segmentIndex << " :";
            dbg << proxyList[segmentIndex].startValue << proxyList[segmentIndex].hasStartValue << proxyList[segmentIndex].endValue << proxyList[segmentIndex].hasEndValue << " -> ";
            dbg << proxyList[segmentIndex].isSteady << proxyList[segmentIndex].rampStartIndex;
         }
            */
      }
   }
}

#endif // NOT ContoursHPP
