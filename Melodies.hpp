#ifndef MelodiesHPP
#define MelodiesHPP

#include <Blocks/Melodies.h>

// unit

Melodies::Unit::Unit()
   : value(0)
{
}

Melodies::Unit::Unit(const Unit& other)
   : value(other.value)
{
}

Melodies::Unit& Melodies::Unit::operator=(const Unit& other)
{
   value = other.value;

   return *this;
}

// melodies

Melodies::Melodies()
   : Abstract::SegmentCrawler()
   , lanes{}
   , zeroSegment()
{
}

void Melodies::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);
}

void Melodies::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);
}

const std::string& Melodies::getName(const uint8_t laneIndex) const
{
   return lanes[laneIndex].name;
}

void Melodies::setName(const uint8_t laneIndex, const std::string& text)
{
   lanes[laneIndex].name = text;
}

const Melodies::Unit& Melodies::getUnit(const uint8_t laneIndex, const uint32_t segmentIndex, const uint8_t tick) const
{
   return getSegment(laneIndex, segmentIndex).at(tick);
}

const Melodies::Segment& Melodies::getSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   const uint32_t proxyIndex = lanes[laneIndex].proxyList.at(segmentIndex);
   const Segment& segment = lanes[laneIndex].segmentMap.at(proxyIndex);

   return segment;
}

bool Melodies::hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   if (lanes[laneIndex].segmentMap.find(segmentIndex) == lanes[laneIndex].segmentMap.end())
      return false;

   return true;
}

void Melodies::setSegment(const uint8_t laneIndex, const uint32_t segmentIndex, const Segment& segment)
{
   lanes[laneIndex].segmentMap[segmentIndex] = segment;
   updateProxies();
}

void Melodies::clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex)
{
   lanes[laneIndex].segmentMap.erase(segmentIndex);
   updateProxies();
}

void Melodies::updateProxies()
{
}

#endif // NOT MelodiesHPP
