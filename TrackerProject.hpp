#ifndef TrackerProjectHPP
#define TrackerProjectHPP

#include <Blocks/TrackerProject.h>

Tracker::Project::Project()
   : Remember::Container()
   , deafaultDivision(this, Tempo::Bar)
   , segmentCount(this, 0)
   , lanes(this)
   , loop(this, false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
   for (uint8_t laneIndex = 0; laneIndex < getLaneCount(); laneIndex++)
      lanes[laneIndex].setup(this);
}

void Tracker::Project::clear()
{
   deafaultDivision = Tempo::Bar;
   segmentCount = 0;

   divisionCounter.setMaxValue(static_cast<Tempo::Division>(deafaultDivision));

   for (uint8_t laneIndex = 0; laneIndex < getLaneCount(); laneIndex++)
      lanes[laneIndex].resize(0, true);

   Remember::Root::setUnsynced();
}

void Tracker::Project::update(const Tempo::Division& newDivision, const uint32_t newSegmentCount)
{
   deafaultDivision = newDivision;
   segmentCount = newSegmentCount;

   divisionCounter.setMaxValue(static_cast<Tempo::Division>(deafaultDivision));

   for (uint8_t laneIndex = 0; laneIndex < getLaneCount(); laneIndex++)
      lanes[laneIndex].resize(segmentCount, false);

   Remember::Root::setUnsynced();
}

void Tracker::Project::clockTick()
{
   if (pastLoop)
      return;

   if (!firstTickDone) // ignore the first clock tick
   {
      firstTickDone = true;
      divisionCounter.nextAndIsMaxValue();
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

const Tempo::Division& Tracker::Project::getDefaultDivison() const
{
   return deafaultDivision.constRef();
}

const uint32_t& Tracker::Project::getSegmentCount() const
{
   return segmentCount.constRef();
}

uint8_t Tracker::Project::getLaneCount() const
{
   return laneCount;
}

Tracker::Lane& Tracker::Project::getLane(const uint8_t laneIndex)
{
   return lanes[laneIndex];
}

const Tracker::Lane& Tracker::Project::getConstLane(const uint8_t laneIndex) const
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

void Tracker::Project::setCurrentSegmentIndex(const uint32_t index)
{
   currentSegmentIndex = index;
}

#endif // NOT TrackerProjectHPP
