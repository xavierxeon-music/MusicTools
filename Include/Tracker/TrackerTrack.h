#ifndef TrackerTrackH
#define TrackerTrackH

#include <Remember.h>

#include "TrackerSegement.h"
namespace Tracker
{
   class Track : public Remember::Container
   {
   public:
      inline Track();

   private:
      using Segments_ = Remember::RefList<Segement>;
   };
} // namespace Tracker

#ifndef TrackerTrackHPP
#include "../../TrackerTrack.hpp"
#endif // NOT TrackerTrackHPP

#endif // NOT TrackerTrackH
