#ifndef ContoursH
#define ContoursH

#include <Abstract/AbstractSegmentCrawler.h>

#include <Tools/BoolField.h>

class Contours : public virtual Abstract::SegmentCrawler
{
public:
   static constexpr uint8_t laneCount = 16;

   enum Flags
   {
      HasStartValue = 1,
      HasEndValue = 2,
   };

   union Segment
   {
      struct
      {
         uint8_t startValue = 0;
         uint8_t endValue = 0;
         uint8_t flags = 0;
         uint8_t steady = 0;
      };
      int32_t value;

      inline Segment();
      inline Segment(const Segment& other);
      inline Segment& operator=(const Segment& other);

      inline void setStartValue(const uint8_t value);
      inline bool hasStartValue() const;

      inline void setEndValue(const uint8_t value);
      inline bool hasEndValue() const;

      inline void setSteady(bool steady);
      inline bool isSteady() const;
   };

public:
   inline Contours();

public:
   inline virtual void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override;
   inline virtual void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override;

   inline const std::string& getName(const uint8_t laneIndex) const;
   inline void setName(const uint8_t laneIndex, const std::string& text);
   inline uint8_t getSegmentValue(const uint8_t laneIndex, const uint32_t segmentIndex, const float& segmentPercentage) const;

   inline const Segment& getSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const; // may point to proxy
   inline bool hasSegment(const uint8_t laneIndex, const uint32_t segmentIndex) const;
   inline void setSegment(const uint8_t laneIndex, const uint32_t segmentIndex, const Segment& segment);
   inline void clearSegment(const uint8_t laneIndex, const uint32_t segmentIndex);

   inline void updateProxies() override;

private:
   using SegmentMap = std::map<uint32_t, Segment>;

   struct Proxy
   {
      uint8_t startValue = 0;
      uint8_t endVlue = 0;

      using List = std::vector<Proxy>;
   };

   struct Lane
   {
      std::string name;
      SegmentMap segmentMap;
      Proxy::List proxyList;
   };

private:
   Lane lanes[laneCount];
   SegmentMap zeroSegment;
};

#ifndef ContoursHPP
#include "../../Contours.hpp"
#endif // NOT ContoursHPP

#endif // NOT ContoursH
