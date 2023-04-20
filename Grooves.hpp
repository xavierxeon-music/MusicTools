#ifndef GroovesHPP
#define GroovesHPP

#include <Blocks/Grooves.h>

Grooves::Grooves()
   : Abstract::SegmentCrawler()
   , beatMap()
   , beatProxyList()
   , gatesMap()
   , gatesProxyList()
   , zeroBeat(getDefaultLength(), BoolField8(0))
   , zeroGates(BoolField8(0))
{
   updateProxies();
}

void Grooves::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);

   zeroBeat = Beat(newDefaultDivision, BoolField8(0));

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

   updateProxies();
}

void Grooves::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);

   if (beatMap.find(segmentIndex) == beatMap.end())
      return;

   const uint8_t tickCount = (0 == length) ? getDefaultLength() : length;

   Beat& beat = beatMap[segmentIndex];
   while (beat.size() > tickCount)
      beat.pop_back();
   while (beat.size() < tickCount)
      beat.push_back(BoolField8(0));
}

BoolField8 Grooves::getTriggers(const uint32_t segmentIndex, const uint8_t tick) const
{
   const Beat beat = getBeat(segmentIndex);
   if (beat.size() <= tick)
      return BoolField8(0);

   return beat.at(tick);
}

const Grooves::Beat& Grooves::getBeat(const uint32_t& segmentIndex) const
{
   if (beatMap.empty())
      return zeroBeat;

   const uint32_t realSegmentIndex = beatProxyList.empty() ? 0 : beatProxyList.at(segmentIndex);
   if (beatMap.find(realSegmentIndex) == beatMap.end())
      return zeroBeat;

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
   updateProxies();
}

void Grooves::clearBeat(const uint32_t& segmentIndex)
{
   if (beatMap.find(segmentIndex) == beatMap.end())
      return;

   beatMap.erase(segmentIndex);
   updateProxies();
}

const Grooves::Gates& Grooves::getGates(const uint32_t& segmentIndex) const
{
   if (gatesMap.empty())
      return zeroGates;

   const uint32_t realSegmentIndex = gatesProxyList.empty() ? 0 : gatesProxyList.at(segmentIndex);
   if (gatesMap.find(realSegmentIndex) == gatesMap.end())
      return zeroGates;

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
   updateProxies();
}

void Grooves::clearGates(const uint32_t& segmentIndex)
{
   gatesMap.erase(segmentIndex);
   updateProxies();
}

void Grooves::updateProxies()
{
   beatProxyList = ProxyList(getSegmentCount(), 0);
   gatesProxyList = ProxyList(getSegmentCount(), 0);

   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      beatProxyList[segmentIndex] = 0;
      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasBeat(proxySegmentIndex))
            continue;

         beatProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }

      gatesProxyList[segmentIndex] = 0;
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
