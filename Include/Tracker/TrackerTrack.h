#ifndef TrackerTrackH
#define TrackerTrackH

#include <Remember.h>

#include "TrackerSegment.h"

namespace Tracker
{
   pyexport class Track : public Remember::Container
   {
   public:
      pyexport enum class Type //
      {
         CV,
         Note,
         Gate,
         Trigger
      };

   public:
      pyexport inline Track();
      inline Track& operator=(const Track& other);

   public:
      pyexport inline void resize(const uint32_t segementCount);
      pyexport inline Segment& getSegment(const uint32_t index);

   private:
      using Name_ = Remember::String;
      using Type_ = Remember::Value<Type>;
      using Steady_ = Remember::Value<bool>;
      using Segments_ = Remember::RefList<Segment>;

   private:
      Name_ name;
      Type_ type;
      Steady_ steady;
      Segments_ segments;
   };
} // namespace Tracker

#ifndef TrackerTrackHPP
#include "../../TrackerTrack.hpp"
#endif // NOT TrackerTrackHPP

#endif // NOT TrackerTrackH
