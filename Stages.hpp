#ifndef StagesHPP
#define StagesHPP

#include <Blocks/Stages.h>

// unit

Stages::Unit::Unit()
   : value(0)
{
}

Stages::Unit::Unit(const Unit& other)
   : value(other.value)
{
}

Stages::Unit& Stages::Unit::operator=(const Unit& other)
{
   value = other.value;

   return *this;
}

// Stages

Stages::Stages()
   : Abstract::SegmentCrawler()
   , lanes{}
   , zeroSegment()
{
}

void Stages::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);
}

void Stages::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);
}

const std::string& Stages::getName(const uint8_t laneIndex) const
{
   return lanes[laneIndex].name;
}

void Stages::setName(const uint8_t laneIndex, const std::string& text)
{
   lanes[laneIndex].name = text;
}

const Stages::Unit& Stages::getUnit(const uint8_t laneIndex, const uint32_t segmentIndex, const uint8_t tick) const
{
   return getSegment(laneIndex, segmentIndex).at(tick);
}

const Stages::Segment& Stages::getSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   const uint32_t proxyIndex = lanes[laneIndex].proxyList.at(segmentIndex);
   const Segment& segment = lanes[laneIndex].segmentMap.at(proxyIndex);

   return segment;
}

bool Stages::hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   if (lanes[laneIndex].segmentMap.find(segmentIndex) == lanes[laneIndex].segmentMap.end())
      return false;

   return true;
}

void Stages::setSegment(const uint8_t laneIndex, const uint32_t segmentIndex, const Segment& segment)
{
   lanes[laneIndex].segmentMap[segmentIndex] = segment;
   updateProxies();
}

void Stages::clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex)
{
   lanes[laneIndex].segmentMap.erase(segmentIndex);
   updateProxies();
}

void Stages::updateProxies()
{
}

#endif // NOT StagesHPP
