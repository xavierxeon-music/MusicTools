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
   updateProxies();
}

void Grooves::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
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
   static BeatMap zeroBeats;
   const uint8_t length = getSegmentLength(segmentIndex);
   if (zeroBeats.find(length) == zeroBeats.end())
      zeroBeats[length] = Beat(length, 0);

   if (beatMap.empty())
      return zeroBeats.at(length);

   const uint32_t realSegmentIndex = beatProxyList.empty() ? 0 : beatProxyList.at(segmentIndex);
   if (beatMap.find(realSegmentIndex) == beatMap.end())
      return zeroBeats.at(length);

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
   static GatesMap zeroGates;
   const uint8_t length = getSegmentLength(segmentIndex);
   if (zeroGates.find(length) == zeroGates.end())
      zeroGates[length] = BoolField8(0);

   if (gatesMap.empty())
      return zeroGates.at(length);

   const uint32_t realSegmentIndex = gatesProxyList.empty() ? 0 : gatesProxyList.at(segmentIndex);
   if (gatesMap.find(realSegmentIndex) == gatesMap.end())
      return zeroGates.at(length);

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

   uint32_t lastBeatIndex = 0;
   uint32_t lastGatesIndex = 0;
   for (uint32_t segmentIndex = 0; segmentIndex < getSegmentCount(); segmentIndex++)
   {
      if (hasBeat(segmentIndex))
         lastBeatIndex = segmentIndex;

      beatProxyList[segmentIndex] = lastBeatIndex;

      if (hasGates(segmentIndex))
         lastGatesIndex = segmentIndex;

      gatesProxyList[segmentIndex] = lastGatesIndex;
   }
}

#endif // NOT GroovesHPP
