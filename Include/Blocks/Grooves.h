#ifndef GroovesH
#define GroovesH

#include <Abstract/AbstractSegmentCrawler.h>

#include <map>

#include <Tools/BoolField.h>

pyexport class Grooves : public Abstract::SegmentCrawler
{
public:
   using State = BoolField8;             // one entry per segment
   using Beat = std::vector<BoolField8>; // one entry per tick

public:
   pyexport inline Grooves();

public:
   pyexport inline BoolField8 getSpikes(const uint32_t segmentIndex, const uint8_t tick) const;
   pyexport inline const Beat& getBeat(const uint32_t& segmentIndex) const; // may point to proxy
   pyexport inline bool hasBeat(const uint32_t& segmentIndex) const;
   pyexport inline void setBeat(const uint32_t& segmentIndex, const Beat& beat);
   pyexport inline void resetBeat(const uint32_t& segmentIndex);

   pyexport inline const State& getState(const uint32_t& segmentIndex) const; // may point to proxy
   pyexport inline bool hasState(const uint32_t& segmentIndex) const;
   pyexport inline void setState(const uint32_t& segmentIndex, const State& state);
   pyexport inline void resetState(const uint32_t& segmentIndex);

private:
   void updateBeatProxyList();
   void updateStateProxyList();

private:
   using BeatMap = std::map<uint32_t, Beat>;        // segement index of beat
   using StateMap = std::map<uint32_t, BoolField8>; // segment index of furrow
   using ProxyList = std::vector<uint32_t>;         // index of the last available State or Beat

private:
   BeatMap beatMap;
   ProxyList beatProxyList;
   StateMap stateMap;
   ProxyList stateProxyList;
};

#ifndef GroovesHPP
#include "../../Grooves.hpp"
#endif // NOT GroovesHPP

#endif // NOT GroovesH
