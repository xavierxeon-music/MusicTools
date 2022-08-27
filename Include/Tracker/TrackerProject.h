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
      pyexport inline void clear(const Tempo::Division& newDivision, const uint32_t newSegmentCount);

      pyexport inline void clockTick();
      pyexport inline void clockReset();

      pyexport inline const std::string getName() const;
      pyexport inline void setName(const std::string& text);

      pyexport inline Tempo::Division getDivison() const;
      pyexport inline uint32_t getSegementCount() const;

      pyexport inline uint8_t getLaneCount() const;
      inline Lane& getLane(const uint8_t laneIndex);

      pyexport inline bool isLooping() const;
      pyexport inline void setLooping(bool on);

   private:
      using Name_ = Remember::String;
      using Division_ = Remember::Value<Tempo::Division>;
      using SegementCount_ = Remember::Value<uint32_t>;
      using Laness_ = Remember::RefArray<Lane, 32>;
      using Loop_ = Remember::Value<bool>;

   private:
      Name_ name;
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
