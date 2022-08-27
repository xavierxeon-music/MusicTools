#ifndef TrackerLaneH
#define TrackerLaneH

#include <Remember.h>

#include "TrackerSegment.h"

namespace Tracker
{
   pyexport class Lane : public Remember::Container
   {

   public:
      pyexport inline Lane();
      inline Lane(const Lane& other);
      inline Lane& operator=(const Lane& other);

   public:
      pyexport inline void resize(const uint32_t segementCount);
      pyexport inline Segment& getSegment(const uint32_t index);

      pyexport inline std::string getName() const;
      pyexport inline void setName(const std::string& text);

   private:
      using Name_ = Remember::String;
      using Segments_ = Remember::RefList<Segment>;

   private:
      Name_ name;
      Segments_ segments;
   };
} // namespace Tracker

#ifndef TrackerLaneHPP
#include "../../TrackerLane.hpp"
#endif // NOT TrackerLaneHPP

#endif // NOT TrackerLaneH
