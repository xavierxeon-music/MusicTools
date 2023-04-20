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

   Q_UNUSED(segmentPercentage)
   Q_UNUSED(proxy)
   return 0;
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
}

#endif // NOT ContoursHPP
