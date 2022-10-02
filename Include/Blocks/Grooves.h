#ifndef GroovesH
#define GroovesH

#include <Abstract/AbstractSegmentCrawler.h>

#include <map>

#include <Tools/BoolField.h>

pyexport class Grooves : public Abstract::SegmentCrawler
{
public:
   using Gate = BoolField8;              // one entry per segment
   using Beat = std::vector<BoolField8>; // one entry per tick

public:
   pyexport inline Grooves();

public:
   pyexport inline BoolField8 getTriggers(const uint32_t segmentIndex, const uint8_t tick) const;
   pyexport inline const Beat& getBeat(const uint32_t& segmentIndex) const; // may point to proxy
   pyexport inline bool hasBeat(const uint32_t& segmentIndex) const;
   pyexport inline void setBeat(const uint32_t& segmentIndex, const Beat& beat);
   pyexport inline void resetBeat(const uint32_t& segmentIndex);

   pyexport inline const Gate& getGate(const uint32_t& segmentIndex) const; // may point to proxy
   pyexport inline bool hasGate(const uint32_t& segmentIndex) const;
   pyexport inline void setGate(const uint32_t& segmentIndex, const Gate& gate);
   pyexport inline void resetGate(const uint32_t& segmentIndex);

private:
   inline void updateBeatProxyList();
   inline void updateGateProxyList();

private:
   using BeatMap = std::map<uint32_t, Beat>;        // segement index of beat
   using GateMap = std::map<uint32_t, BoolField8>;  // segment index of furrow
   using ProxyList = std::vector<uint32_t>;         // index of the last available Gate or Beat

private:
   BeatMap beatMap;
   ProxyList beatProxyList;
   GateMap gateMap;
   ProxyList gateProxyList;
};

#ifndef GroovesHPP
#include "../../Grooves.hpp"
#endif // NOT GroovesHPP

#endif // NOT GroovesH
