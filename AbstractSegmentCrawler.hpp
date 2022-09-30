#ifndef AbstractSegmentCrawlerHPP
#define AbstractSegmentCrawlerHPP

#include <Abstract/AbstractSegmentCrawler.h>

Abstract::SegmentCrawler::SegmentCrawler()
   : Remember::Container()
   , deafaultDivision(this, Tempo::Bar)
   , segmentCount(this, 0)
   , loop(this, false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
}

void Abstract::SegmentCrawler::clear()
{
   deafaultDivision = Tempo::Bar;
   segmentCount = 0;

   divisionCounter.setMaxValue(deafaultDivision);

   Remember::Root::setUnsynced();
}

void Abstract::SegmentCrawler::update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount)
{
   deafaultDivision = newDefaultDivision;
   segmentCount = newSegmentCount;

   divisionCounter.setMaxValue(deafaultDivision);

   Remember::Root::setUnsynced();
}

void Abstract::SegmentCrawler::clockTick()
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

void Abstract::SegmentCrawler::clockReset()
{
   divisionCounter.reset();
   currentSegmentIndex = 0;
   pastLoop = false;
}

const uint8_t& Abstract::SegmentCrawler::getDefaultDivision() const
{
   return deafaultDivision.constRef();
}

const uint32_t& Abstract::SegmentCrawler::getSegmentCount() const
{
   return segmentCount.constRef();
}

uint8_t Abstract::SegmentCrawler::getSegmentLength(const uint32_t index) const
{
   (void)index;
   // TODO allow for individual segment lengths
   return deafaultDivision.constRef();
}

bool Abstract::SegmentCrawler::isLooping() const
{
   return loop;
}

void Abstract::SegmentCrawler::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
}

const uint32_t& Abstract::SegmentCrawler::getCurrentSegmentIndex() const
{
   return currentSegmentIndex;
}

void Abstract::SegmentCrawler::setCurrentSegmentIndex(const uint32_t index)
{
   currentSegmentIndex = index;
}

uint8_t Abstract::SegmentCrawler::getCurrentSegmentTick() const
{
   return divisionCounter.getCurrentValue();
}

float Abstract::SegmentCrawler::getCurrentSegmentPrecentage(const float tickPercentage) const
{
   float currentTick = divisionCounter.getCurrentValue();
   const float maxTick = divisionCounter.getMaxValue();

   if (currentTick != maxTick && 0.0 < tickPercentage && 1.0 > tickPercentage)
      currentTick += tickPercentage;

   const float percentage = currentTick / maxTick;

   return percentage;
}

#endif // NOT AbstractSegmentCrawlerHPP
