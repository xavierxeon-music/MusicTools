#ifndef TrackerLaneH
#define TrackerLaneH

#include <MusicTools.h>

#include <Remember.h>

namespace Tracker
{
   pyexport class Lane : public Remember::Container
   {

   public:
      pyexport inline Lane();
      inline Lane(const Lane& other);
      inline Lane& operator=(const Lane& other);

   public:
      pyexport inline void resize(const uint32_t segmentCount);

      pyexport inline std::string getName() const;
      pyexport inline void setName(const std::string& text);

      pyexport inline uint8_t getSegmentValue(const uint32_t index, const float& percentage) const;

      pyexport inline void resetSegment(const uint32_t index);

      pyexport inline uint8_t getSegmentStartValue(const uint32_t index) const;
      pyexport inline bool hasSegmentStartValue(const uint32_t index) const;
      pyexport inline void setSegmentStartValue(const uint32_t index, const uint8_t value);

      pyexport inline uint8_t getSegmentEndValue(const uint32_t index) const;
      pyexport inline bool hasSegmentEndValue(const uint32_t index) const;
      pyexport inline void setSegmentEndValue(const uint32_t index, const uint8_t value);

      pyexport inline bool hasSegmentValues(const uint32_t index) const;

      pyexport inline bool isSegmentSteady(const uint32_t index) const;
      pyexport inline void setSegmentSteady(const uint32_t index, bool on);

   private:
      using Name_ = Remember::String;
      using Value_ = Remember::Value<uint8_t>;
      using Bool_ = Remember::Value<bool>;

      struct Segment : public Remember::Container
      {
         Value_ startValue;
         Bool_ startExists;

         Value_ endValue;
         Bool_ endExists;

         Bool_ steady;

         inline Segment();
      };

      struct Proxy
      {
         uint8_t startValue = 0;
         uint8_t endValue = 0;

         using List = std::vector<Proxy>;
      };

      using Segments_ = Remember::RefList<Segment>;

   private:
      inline void updateProxyList() const;

   private:
      Name_ name;
      Segments_ segments;

      mutable bool dirty;
      mutable Proxy::List proxyList;
   };
} // namespace Tracker

#ifndef TrackerLaneHPP
#include "../../TrackerLane.hpp"
#endif // NOT TrackerLaneHPP

#endif // NOT TrackerLaneH
