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
   beatMap[0] = Beat(getDefaultDivision(), BoolField8(0));
   updateBeatProxyList();

   gatesMap[0] = BoolField8(0);
   updateGatesProxyList();
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
   updateBeatProxyList();
}

void Grooves::resetBeat(const uint32_t& segmentIndex)
{
   if (beatMap.find(segmentIndex) == beatMap.end())
      return;

   beatMap.erase(segmentIndex);
   updateBeatProxyList();
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
   updateGatesProxyList();
}

void Grooves::resetGates(const uint32_t& segmentIndex)
{
   gatesMap.erase(segmentIndex);
   updateGatesProxyList();
}

void Grooves::updateBeatProxyList()
{
   beatProxyList = ProxyList(getSegmentCount(), 0);
   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasBeat(proxySegmentIndex))
            continue;

         beatProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }
   }
}

void Grooves::updateGatesProxyList()
{
   gatesProxyList = ProxyList(getSegmentCount(), 0);
   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
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
