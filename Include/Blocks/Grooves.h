#ifndef GroovesH
#define GroovesH

#include <Abstract/AbstractSegmentCrawler.h>

#include <map>

#include <Tools/BoolField.h>

class Grooves : public virtual Abstract::SegmentCrawler
{
public:
   using Gates = BoolField8;             // one entry per segment
   using Beat = std::vector<BoolField8>; // one entry per tick

public:
   inline Grooves();

public:
   inline virtual void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override;
   inline virtual void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override;

   inline BoolField8 getTriggers(const uint32_t segmentIndex, const uint8_t tick) const;

   inline const Beat& getBeat(const uint32_t& segmentIndex) const; // may point to proxy
   inline bool hasBeat(const uint32_t& segmentIndex) const;
   inline void setBeat(const uint32_t& segmentIndex, const Beat& beat);
   inline void clearBeat(const uint32_t& segmentIndex);

   inline const Gates& getGates(const uint32_t& segmentIndex) const; // may point to proxy
   inline bool hasGates(const uint32_t& segmentIndex) const;
   inline void setGates(const uint32_t& segmentIndex, const Gates& gates);
   inline void clearGates(const uint32_t& segmentIndex);

   inline void updateProxies() override;

private:
   using BeatMap = std::map<uint32_t, Beat>;        // segement index of beat
   using GatesMap = std::map<uint32_t, BoolField8>; // segment index of furrow
   using ProxyList = std::vector<uint32_t>;         // index of the last available Gate or Beat

private:
   BeatMap beatMap;
   ProxyList beatProxyList;
   GatesMap gatesMap;
   ProxyList gatesProxyList;

   Beat zeroBeat;
   const BoolField8 zeroGates;
};

#ifndef GroovesHPP
#include "../../Grooves.hpp"
#endif // NOT GroovesHPP

#endif // NOT GroovesH
