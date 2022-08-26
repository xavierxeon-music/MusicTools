#ifndef TrackerBankH
#define TrackerBankH

#include <Remember.h>

#include "TrackerTrack.h"

namespace Tracker
{
   class Bank : public Remember::Container
   {
   public:
      inline Bank();
      inline Bank(const Bank& other);

   private:
      using Tracks_ = Remember::RefArray<Track, 8>;

   private:
      Tracks_ tracks;
   };
} // namespace Tracker

#ifndef TrackerBankHPP
#include "../../TrackerBank.hpp"
#endif // NOT TrackerBankHPP

#endif // NOT TrackerBankH
