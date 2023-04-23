#ifndef StagesHPP
#define StagesHPP

#include <Blocks/Stages.h>

// unit

Stages::Unit::Unit()
   : value(0)
{
   value1 = 36;
   value2 = 127;
   length = 0;
   propability = 255;
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
{
}

void Stages::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);

   bool isDefault = false;
   for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
   {
      Lane& lane = lanes[laneIndex];
      for (SegmentMap::iterator it = lane.segmentMap.end(); it != lane.segmentMap.end(); it++)
      {
         getSegmentLength(it->first, &isDefault);
         if (!isDefault)
            continue;

         Segment& segment = it->second;
         while (segment.size() > newDefaultDivision)
            segment.pop_back();
         while (segment.size() < newDefaultDivision)
            segment.push_back(Unit());
      }
   }

   updateProxies();
}

void Stages::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);

   for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
   {
      Lane& lane = lanes[laneIndex];
      for (SegmentMap::iterator it = lane.segmentMap.end(); it != lane.segmentMap.end(); it++)
      {
         if (lane.segmentMap.find(segmentIndex) == lane.segmentMap.end())
            continue;

         const uint8_t tickCount = (0 == length) ? getDefaultLength() : length;

         Segment& segment = lane.segmentMap[segmentIndex];
         while (segment.size() > tickCount)
            segment.pop_back();
         while (segment.size() < tickCount)
            segment.push_back(Unit());
      }
   }
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
   static SegmentMap zeroSegments;
   const uint8_t length = getSegmentLength(segmentIndex);
   if (!zeroSegments.contains(length))
      zeroSegments[length] = Segment(length, Unit());

   const Lane& lane = lanes[laneIndex];
   if (lane.segmentMap.empty())
      return zeroSegments.at(length);

   const uint32_t realSegmentIndex = lane.proxyList.empty() ? 0 : lane.proxyList.at(segmentIndex);
   if (lane.segmentMap.find(realSegmentIndex) == lane.segmentMap.end())
      return zeroSegments.at(length);

   const Segment& segment = lane.segmentMap.at(realSegmentIndex);
   return segment;
}

bool Stages::hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const
{
   const Lane& lane = lanes[laneIndex];
   if (lane.segmentMap.find(segmentIndex) == lane.segmentMap.end())
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
   for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
   {
      Lane& lane = lanes[laneIndex];
      lane.proxyList = ProxyList(getSegmentCount(), 0);

      uint32_t lastIndex = 0;
      for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
      {
         if (hasSegment(laneIndex, segmentIndex))
            lastIndex = segmentIndex;

         lane.proxyList[segmentIndex] = lastIndex;
      }
   }
}

#endif // NOT StagesHPP
