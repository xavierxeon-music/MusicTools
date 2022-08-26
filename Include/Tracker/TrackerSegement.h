#ifndef TrackerSegementH
#define TrackerSegementH

#include <Remember.h>

namespace Tracker
{
   class Segement : public Remember::Container
   {
   public:
      inline Segement();
   };
} // namespace Tracker

#ifndef TrackerSegementHPP
#include "../../TrackerSegement.hpp"
#endif // NOT TrackerSegementHPP

#endif // NOT TrackerSegementH
