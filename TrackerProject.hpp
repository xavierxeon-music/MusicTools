#ifndef TrackerProjectHPP
#define TrackerProjectHPP

#include <Blocks/TrackerProject.h>

Tracker::Project::Project()
   : Remember::Container()
   , division(this, Tempo::Bar)
   , segmentCount(this, 0)
   , lanes(this)
   , loop(this, false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
}

void Tracker::Project::clear(const Tempo::Division& newDivision, const uint32_t newSegmentCount)
{
   division = newDivision;
   segmentCount = newSegmentCount;

   divisionCounter.setMaxValue(static_cast<Tempo::Division>(division));

   for (uint8_t laneIndex = 0; laneIndex < getLaneCount(); laneIndex++)
      lanes[laneIndex].resize(segmentCount);

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

Tempo::Division Tracker::Project::getDivison() const
{
   return division;
}

uint32_t Tracker::Project::getSegementCount() const
{
   return segmentCount;
}

uint8_t Tracker::Project::getLaneCount() const
{
   return lanes.getSize();
}

Tracker::Lane& Tracker::Project::getLane(const uint8_t laneIndex)
{
   return lanes[laneIndex];
}

const Tracker::Lane& Tracker::Project::getLane(const uint8_t laneIndex) const
{
   return lanes[laneIndex];
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

const uint32_t& Tracker::Project::getCurrentSegmentIndex() const
{
   return currentSegmentIndex;
}

#endif // NOT TrackerProjectHPP
