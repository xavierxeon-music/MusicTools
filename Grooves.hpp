#ifndef GroovesHPP
#define GroovesHPP

#include <Blocks/Grooves.h>

Grooves::Grooves()
   : Abstract::SegmentCrawler()
   , beatMap()
   , beatProxyList()
   , gatesMap()
   , gatesProxyList()
{
   updateProxyLists();
}

void Grooves::clear()
{
   Abstract::SegmentCrawler::clear();
}

void Grooves::update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);

   bool isDefault = false;
   for (BeatMap::iterator it = beatMap.end(); it != beatMap.end(); it++)
   {
      getSegmentLength(it->first, &isDefault);
      if (!isDefault)
         continue;

      Beat& beat = it->second;
      while (beat.size() > newDefaultDivision)
         beat.pop_back();
      while (beat.size() < newDefaultDivision)
         beat.push_back(BoolField8(0));
   }

   updateProxyLists();
}

void Grooves::setSegmentLength(const uint32_t segmentIndex, const uint8_t& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);

   if (beatMap.find(segmentIndex) == beatMap.end())
      return;

   const uint8_t tickCount = (0 == length) ? getDefaultDivision() : length;

   Beat& beat = beatMap[segmentIndex];
   while (beat.size() > tickCount)
      beat.pop_back();
   while (beat.size() < tickCount)
      beat.push_back(BoolField8(0));
}

BoolField8 Grooves::getTriggers(const uint32_t segmentIndex, const uint8_t tick) const
{
   return getBeat(segmentIndex).at(tick);
}

const Grooves::Beat& Grooves::getBeat(const uint32_t& segmentIndex) const
{
   const uint32_t realSegmentIndex = beatProxyList.empty() ? 0 : beatProxyList.at(segmentIndex);
   return beatMap.at(realSegmentIndex);
}

bool Grooves::hasBeat(const uint32_t& segmentIndex) const
{
   if (beatMap.find(segmentIndex) == beatMap.end())
      return false;

   return true;
}

void Grooves::setBeat(const uint32_t& segmentIndex, const Beat& beat)
{
   beatMap[segmentIndex] = beat;
   updateProxyLists();
}

void Grooves::clearBeat(const uint32_t& segmentIndex)
{
   if (beatMap.find(segmentIndex) == beatMap.end())
      return;

   beatMap.erase(segmentIndex);
   updateProxyLists();
}

const Grooves::Gates& Grooves::getGates(const uint32_t& segmentIndex) const
{
   const uint32_t realSegmentIndex = gatesProxyList.empty() ? 0 : gatesProxyList.at(segmentIndex);
   return gatesMap.at(realSegmentIndex);
}

bool Grooves::hasGates(const uint32_t& segmentIndex) const
{
   if (gatesMap.find(segmentIndex) == gatesMap.end())
      return false;

   return true;
}

void Grooves::setGates(const uint32_t& segmentIndex, const Gates& gates)
{
   gatesMap[segmentIndex] = gates;
   updateProxyLists();
}

void Grooves::clearGates(const uint32_t& segmentIndex)
{
   gatesMap.erase(segmentIndex);
   updateProxyLists();
}

void Grooves::updateProxyLists()
{
   beatProxyList = ProxyList(getSegmentCount(), 0);
   gatesProxyList = ProxyList(getSegmentCount(), 0);

   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasBeat(proxySegmentIndex))
            continue;

         beatProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }

      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasGates(proxySegmentIndex))
            continue;

         gatesProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }
   }
}

#endif // NOT GroovesHPP
