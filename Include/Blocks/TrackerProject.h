#ifndef TrackerProjectH
#define TrackerProjectH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

#include "TrackerLane.h"

namespace Tracker
{
   pyexport class Project : public Remember::Container
   {
   public:
      pyexport inline Project();

   public:
      pyexport inline void clear();
      pyexport inline void update(const Tempo::Division& newDivision, const uint32_t newSegmentCount);

      pyexport inline void clockTick();
      pyexport inline void clockReset();

      pyexport inline const Tempo::Division& getDivison() const;
      pyexport inline const uint32_t& getSegmentCount() const;

      pyexport inline uint8_t getLaneCount() const;
      pyexport inline Lane& getLane(const uint8_t laneIndex);
      inline const Lane& getLane(const uint8_t laneIndex) const;

      pyexport inline bool isLooping() const;
      pyexport inline void setLooping(bool on);

      pyexport inline const uint32_t& getCurrentSegmentIndex() const;

   private:
      using Division_ = Remember::Value<Tempo::Division>;
      using SegementCount_ = Remember::Value<uint32_t>;
      using Laness_ = Remember::RefArray<Lane, 32>;
      using Loop_ = Remember::Value<bool>;

   private:
      Division_ division;
      SegementCount_ segmentCount;
      Laness_ lanes;
      Loop_ loop;

      uint32_t currentSegmentIndex;
      Counter divisionCounter;
      bool pastLoop;
      bool firstTickDone;
   };
} // namespace Tracker

#ifndef TrackerProjectHPP
#include "../../TrackerProject.hpp"
#endif // NOT TrackerProjectHPP

#endif // NOT TrackerProjectH
