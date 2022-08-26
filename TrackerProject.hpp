#ifndef TrackerProjectHPP
#define TrackerProjectHPP

#include <Tracker/TrackerProject.h>

Tracker::Project::Project()
   : Remember::Container()
   , name(this, "")
   , division(this, Tempo::Bar)
   , segmentCount(this, 0)
   , banks(this)
   , loop(this, false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
}

void Tracker::Project::clear(const uint8_t bankCount, const Tempo::Division& newDivision, const uint32_t newSegementCount)
{
   division = newDivision;
   segmentCount = newSegementCount;

   divisionCounter.setMaxValue(static_cast<Tempo::Division>(division));

   banks.clear();
   for (uint8_t index = 0; index < bankCount; index++)
   {
      Bank bank;
      bank.init(segmentCount);
      banks.append(bank);
   }

   Remember::Root::setUnsynced();
}

void Tracker::Project::clockTick()
{
   if (pastLoop)
      return;

   if (!firstTickDone) // ignore the first clock tick
   {
      firstTickDone = true;
      return;
   }

   if (!divisionCounter.nextAndIsMaxValue())
      return;

   currentSegmentIndex++;
   if (currentSegmentIndex == segmentCount)
   {
      if (loop)
         currentSegmentIndex = 0;
      else
         pastLoop = true;
   }
}

void Tracker::Project::clockReset()
{
   divisionCounter.reset();
   currentSegmentIndex = 0;
   pastLoop = false;
}

const std::string Tracker::Project::getName() const
{
   return name;
}

void Tracker::Project::setName(const std::string& text)
{
   name = text;
   Remember::Root::setUnsynced();
}

Tempo::Division Tracker::Project::getDivison() const
{
   return division;
}

uint32_t Tracker::Project::getSegementCount() const
{
   return segmentCount;
}

uint8_t Tracker::Project::getBankCount() const
{
   return banks.size();
}

Tracker::Bank& Tracker::Project::getBank(const uint8_t index)
{
   return banks[index];
}

bool Tracker::Project::isLooping() const
{
   return loop;
}

void Tracker::Project::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerProjectHPP
