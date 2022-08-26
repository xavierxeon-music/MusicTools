#ifndef TrackerBankH
#define TrackerBankH

#include <Remember.h>

#include "TrackerTrack.h"

namespace Tracker
{
   pyexport class Bank : public Remember::Container
   {
   public:
      pyexport inline Bank();
      inline Bank(const Bank& other);

   public:
      inline void init(const uint32_t newSegmentCount);

   private:
      using Tracks_ = Remember::RefArray<Track, 8>;

   private:
      Tracks_ tracks;
      uint32_t segmentCount;
   };
} // namespace Tracker

#ifndef TrackerBankHPP
#include "../../TrackerBank.hpp"
#endif // NOT TrackerBankHPP

#endif // NOT TrackerBankH
