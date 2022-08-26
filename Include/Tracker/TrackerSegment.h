#ifndef TrackerSegmentH
#define TrackerSegmentH

#include <MusicTools.h>
#include <Remember.h>

namespace Tracker
{
   pyexport class Segment : public Remember::Container
   {
   public:
      pyexport inline Segment();
      inline Segment(const Segment& other);

   public:
      pyexport inline uint8_t getStartValue() const;
      pyexport inline bool hasStartValue() const;
      pyexport inline void setStartValue(const uint8_t value);

      pyexport inline uint8_t getEndValue() const;
      pyexport inline bool hasEndValue() const;
      pyexport inline void setEndValue(const uint8_t value);

   private:
      using Value_ = Remember::Value<uint8_t>;
      using Exists_ = Remember::Value<bool>;

   private:
      Value_ startValue;
      Exists_ startExists;
      Value_ endValue;
      Exists_ endExists;
   };
} // namespace Tracker

#ifndef TrackerSegmentHPP
#include "../../TrackerSegment.hpp"
#endif // NOT TrackerSegmentHPP

#endif // NOT TrackerSegmentH
