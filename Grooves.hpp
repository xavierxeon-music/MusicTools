#ifndef GroovesHPP
#define GroovesHPP

#include <Blocks/Grooves.h>

Grooves::Grooves()
   : Abstract::SegmentCrawler()
   , beatMap()
   , beatProxyList()
   , stateMap()
   , stateProxyList()
{
   beatMap[0] = Beat(getDefaultDivision(), BoolField8(0));
   updateBeatProxyList();

   stateMap[0] = BoolField8(0);
   updateStateProxyList();
}

BoolField8 Grooves::getSpikes(const uint32_t segmentIndex, const uint8_t tick) const
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

const Grooves::State& Grooves::getState(const uint32_t& segmentIndex) const
{
   const uint32_t realSegmentIndex = stateProxyList.empty() ? 0 : stateProxyList.at(segmentIndex);
   return stateMap.at(realSegmentIndex);
}

bool Grooves::hasState(const uint32_t& segmentIndex) const
{
   if (stateMap.find(segmentIndex) == stateMap.end())
      return false;

   return true;
}

void Grooves::setState(const uint32_t& segmentIndex, const State& state)
{
   stateMap[segmentIndex] = state;
   updateStateProxyList();
}

void Grooves::resetState(const uint32_t& segmentIndex)
{
   stateMap.erase(segmentIndex);
   updateStateProxyList();
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

void Grooves::updateStateProxyList()
{
   stateProxyList = ProxyList(getSegmentCount(), 0);
   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      for (uint32_t proxySegmentIndex = segmentIndex; proxySegmentIndex > 0; proxySegmentIndex--)
      {
         if (!hasState(proxySegmentIndex))
            continue;

         stateProxyList[segmentIndex] = proxySegmentIndex;
         break;
      }
   }
}

#endif // NOT GroovesHPP
