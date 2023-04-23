#ifndef StagesH
#define StagesH

#include <Abstract/AbstractSegmentCrawler.h>

class Stages : public virtual Abstract::SegmentCrawler
{
public:
   static constexpr uint8_t laneCount = 8;

   union Unit
   {
      struct
      {
         uint8_t propability = 255; // 0 - 255
         uint8_t value1 = 36;       // eg. midi pitch 0 - 127;
         uint8_t length = 0;        // 0 - 255 ( = full tick)
         uint8_t value2 = 0;        // eg. midi velocity 0 - 127
      };
      int32_t value;

      inline Unit();
      inline Unit(const Unit& other);
      inline Unit& operator=(const Unit& other);
   };

   using Segment = std::vector<Unit>; // one Unit per tick

public:
   inline Stages();

public:
   inline virtual void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override;
   inline virtual void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override;

   inline const std::string& getName(const uint8_t laneIndex) const;
   inline void setName(const uint8_t laneIndex, const std::string& text);
   inline const Unit& getUnit(const uint8_t laneIndex, const uint32_t segmentIndex, const uint8_t tick) const;

   inline const Segment& getSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const; // may point to proxy
   inline bool hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const;
   inline void setSegment(const uint8_t laneIndex, const uint32_t segmentIndex, const Segment& segment);
   inline void clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex);

   inline void updateProxies() override;

private:
   using SegmentMap = std::map<uint32_t, Segment>;
   using ProxyList = std::vector<uint32_t>; // index of the last available Segment

   struct Lane
   {
      std::string name;
      SegmentMap segmentMap;
      ProxyList proxyList;
   };

private:
   Lane lanes[laneCount];
};

#ifndef StagesHPP
#include "../../Stages.hpp"
#endif // NOT StagesHPP

#endif // NOT StagesH
