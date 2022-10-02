#ifndef GroovesHPP
#define GroovesHPP

#include <Blocks/Grooves.h>

Grooves::Grooves()
   : Abstract::SegmentCrawler()
   , beatMap()
   , beatProxyList()
   , gateMap()
   , gateProxyList()
{
   beatMap[0] = Beat(getDefaultDivision(), BoolField8(255));
   updateBeatProxyList();

   gateMap[0] = BoolField8(0);
   updateGateProxyList();
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

const Grooves::Gate& Grooves::getGate(const uint32_t& segmentIndex) const
{
   const uint32_t realSegmentIndex = gateProxyList.empty() ? 0 : gateProxyList.at(segmentIndex);
   return gateMap.at(realSegmentIndex);
}

bool Grooves::hasGate(const uint32_t& segmentIndex) const
{
   if (gateMap.find(segmentIndex) == gateMap.end())
      return false;

   return true;
}

void Grooves::setGate(const uint32_t& segmentIndex, const Gate& gate)
{
   gateMap[segmentIndex] = gate;
   updateGateProxyList();
}

void Grooves::resetGate(const uint32_t& segmentIndex)
{
   gateMap.erase(segmentIndex);
   updateGateProxyList();
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

void Grooves::updateGateProxyList()
{
   gateProxyList = ProxyList(getSegmentCount(), 0);
   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasGate(proxySegmentIndex))
            continue;

         gateProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }
   }
}

#endif // NOT GroovesHPP
