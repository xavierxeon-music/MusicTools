#ifndef TrackerBankHPP
#define TrackerBankHPP

#include <Tracker/TrackerBank.h>

Tracker::Bank::Bank()
   : Remember::Container()
   , tracks(this)
{
}

Tracker::Bank::Bank(const Bank& other)
   : Bank()
{
}

#endif // NOT TrackerBankHPP
