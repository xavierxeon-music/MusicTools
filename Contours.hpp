#ifndef ContoursHPP
#define ContoursHPP

#include <Blocks/Contours.h>

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
   updateProxyList();
}

void Contours::clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex)
{
   lanes[laneIndex].segmentMap.erase(segmentIndex);
   updateProxyList();
}

void Contours::updateProxyList()
{
}

#endif // NOT ContoursHPP
