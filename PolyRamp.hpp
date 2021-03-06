#ifndef PolyRampHPP
#define PolyRampHPP

#include <Blocks/PolyRamp.h>

#include <Tools/Variable.h>

// stage

PolyRamp::Stage::Stage(const uint8_t& startHeight, const uint8_t& endHeight, const uint8_t& stageLength)
   : Remember::Container()
   , startHeight(this, startHeight)
   , endHeight(this, endHeight)
   , stageLength(this, stageLength)
{
}

PolyRamp::Stage::Stage(const Stage& other)
   : Remember::Container()
   , startHeight(this, 0)
   , endHeight(this, 0)
   , stageLength(this, 0)
{
   *this = other;
}

PolyRamp::Stage::~Stage()
{
   // NEED virtual destructor, else compiler warning!
}

PolyRamp::Stage& PolyRamp::Stage::operator=(const Stage& other)
{
   startHeight = other.startHeight;
   endHeight = other.endHeight;
   stageLength = other.stageLength;

   return *this;
}

// graph

PolyRamp::PolyRamp()
   : Remember::Container()
   , stepSize(this, Tempo::Division::Bar)
   , polyRampLength(this, 0)
   , stages(this)
   , loop(this, true)
   , pastLoop(false)
   , currentStageIndex(0)
   , stepSizeCounter(1)
   , stepsTaken(0)
   , stageLengthCounter(1)
   , firstTickDone(false)
{
}

void PolyRamp::clear()
{
   stepSize = Tempo::Division::Bar;
   polyRampLength = 0;
   stages.clear();
   loop = true;

   clockReset();
}

void PolyRamp::clockTick()
{
   if (!isValid() || pastLoop)
      return;

   if (!firstTickDone) // ignore the first clock tick
   {
      firstTickDone = true;
      return;
   }

   if (stepSizeCounter.nextAndIsMaxValue())
   {
      if (stageLengthCounter.nextAndIsMaxValue())
      {
         uint32_t duration = 0;
         do
         {
            stepsTaken += stages[currentStageIndex].stageLength;
            currentStageIndex++;
            if (currentStageIndex == stages.size()) // end of graph
            {
               if (!loop)
               {
                  pastLoop = true;
                  return;
               }
               // TODO not loop
               stepsTaken = 0;
               currentStageIndex = 0;
            }

            duration = compileStageLength(currentStageIndex);
         }
         while (0 == duration);
         stageLengthCounter.setMaxValue(compileStageLength(currentStageIndex));
      }
   }

   //qDebug() << __FUNCTION__ << stepSizeCounter.getCurrentValue() << stageLengthCounter.getCurrentValue();
}

void PolyRamp::clockReset()
{
   stepSizeCounter.reset();
   stageLengthCounter.reset();

   stepSizeCounter.setMaxValue(static_cast<Tempo::Division>(stepSize));
   currentStageIndex = 0;

   if (isValid())
   {
      uint32_t duration = compileStageLength(currentStageIndex);
      while (0 == duration)
      {
         currentStageIndex++;
         duration = compileStageLength(currentStageIndex);
      }
      stageLengthCounter.setMaxValue(duration);
   }
   else
   {
      stageLengthCounter.setMaxValue(0);
   }

   firstTickDone = false;
   stepsTaken = 0;
   pastLoop = false;
}

uint8_t PolyRamp::getCurrentStageIndex() const
{
   return currentStageIndex;
}

float PolyRamp::getCurrentStagePercentage(const float& precentToNextTick) const
{
   if (!isValid())
      return 0.0;

   const float tickContribution = static_cast<float>(precentToNextTick + stepSizeCounter.getCurrentValue()) / static_cast<float>(stepSizeCounter.getMaxValue());
   const float stepContribution = static_cast<float>(stageLengthCounter.getCurrentValue());
   const float duration = static_cast<float>(compileStageLength(currentStageIndex));
   if (0.0 == duration)
      return 0.0;

   const float percentage = (tickContribution + stepContribution) / duration;
   return percentage;
}

float PolyRamp::getCurrentValue(const float& precentToNextTick) const
{
   if (!isValid() || pastLoop)
      return 0.0;

   const float startValue = stages[currentStageIndex].startHeight;
   const float endValue = stages[currentStageIndex].endHeight;

   const float percentage = getCurrentStagePercentage(precentToNextTick);
   const float diffValue = percentage * (endValue - startValue);

   const float value = startValue + diffValue;
   return value;
}

bool PolyRamp::isValid() const
{
   if (0 == stages.size())
      return false;

   if (0 == polyRampLength)
      return false;

   return true;
}

Tempo::Division PolyRamp::getStepSize() const
{
   return stepSize;
}

void PolyRamp::setStepSize(const Tempo::Division& newStepSize)
{
   stepSize = newStepSize;
   Remember::Root::setUnsynced();
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize));
}

void PolyRamp::changeStepSize(bool longer)
{
   using StepSizeOrder = std::vector<Tempo::Division>;
   static const StepSizeOrder order = {Tempo::Division::Sixteenth, Tempo::Division::Eigth, Tempo::Division::Quarter, Tempo::Division::Bar};

   Variable::Enum<Tempo::Division> var(stepSize, order, true);

   var.change(longer);

   Remember::Root::setUnsynced();
   clockReset();
}

uint32_t PolyRamp::getLength() const
{
   return polyRampLength;
}

PolyRamp::LengthStatus PolyRamp::setLength(const uint32_t newLength, bool autoDiscard)
{
   uint8_t keepUntilIndex = 0;
   uint32_t testLength = 0;
   for (uint8_t index = 0; index < stages.size(); index++)
   {
      testLength += stages[index].stageLength;
      if (testLength >= newLength)
         break;
      keepUntilIndex = index;
   }

   const uint8_t cutoffIndex = keepUntilIndex + 1;

   LengthStatus result = (polyRampLength == newLength) ? LengthStatus::Kept : LengthStatus::Changed;
   if (autoDiscard)
   {
      polyRampLength = newLength;
      while (cutoffIndex < stages.size())
      {
         stages.remove(cutoffIndex);
      }
   }
   else
   {
      if (0 != stages.size() && cutoffIndex > stages.size())
         return LengthStatus::Error;

      polyRampLength = newLength;
   }

   Remember::Root::setUnsynced();
   clockReset();
   return result;
}

void PolyRamp::trimLength()
{
   uint32_t newLength = 0;
   for (uint8_t index = 0; index < stages.size(); index++)
      newLength += stages[index].stageLength;

   polyRampLength = newLength;

   Remember::Root::setUnsynced();
   clockReset();
}

uint8_t PolyRamp::getStageCount() const
{
   return stages.size();
}

PolyRamp::LengthStatus PolyRamp::addStage(const uint8_t& afterIndex, const uint32_t& numberOfPolyRamps)
{
   if (0 == numberOfPolyRamps)
      return LengthStatus::Error;

   if (255 == stages.size())
      return LengthStatus::Error;

   for (uint32_t counter = 0; counter < numberOfPolyRamps; counter++)
   {
      Stage stage;
      stages.insert(stage, afterIndex + 1);

      if (255 == stages.size())
         break;
   }

   Remember::Root::setUnsynced();
   clockReset();
   return LengthStatus::Kept;
}

void PolyRamp::moveStage(const uint8_t& fromIndex, const uint8_t& toIndex)
{
   if (fromIndex == toIndex)
      return;

   Stage stageCopy = stages[fromIndex];

   stages.remove(fromIndex);
   stages.insert(stageCopy, toIndex);

   Remember::Root::setUnsynced();
   clockReset();
}

void PolyRamp::removeStage(const uint8_t& index)
{
   stages.remove(index);
   Remember::Root::setUnsynced();
   clockReset();
}

uint8_t PolyRamp::getStageStartHeight(const uint8_t& index) const
{
   return stages[index].startHeight;
}

void PolyRamp::setStageStartHeight(const uint8_t& index, const uint8_t& startHeight)
{
   stages[index].startHeight = startHeight;
   Remember::Root::setUnsynced();
}

uint8_t PolyRamp::getStageEndHeight(const uint8_t& index) const
{
   return stages[index].endHeight;
}

void PolyRamp::setStageEndHeight(const uint8_t& index, const uint8_t& endHeight)
{
   stages[index].endHeight = endHeight;
   Remember::Root::setUnsynced();
}

uint8_t PolyRamp::getStageLength(const uint8_t& index) const
{
   return stages[index].stageLength;
}

PolyRamp::LengthStatus PolyRamp::setStageLength(const uint8_t& index, const uint8_t& stageLength, bool expandLength)
{
   uint32_t newLength = stageLength;
   for (uint8_t stageIndex = 0; stageIndex < stages.size(); stageIndex++)
   {
      if (index == stageIndex)
         continue;
      newLength += stages[stageIndex].stageLength;
   }

   if (newLength > polyRampLength)
   {
      if (expandLength)
         polyRampLength = newLength;
      else
         return LengthStatus::Error;
   }
   stages[index].stageLength = stageLength;

   Remember::Root::setUnsynced();
   clockReset();
   return LengthStatus::Changed;
}

bool PolyRamp::isLooping() const
{
   return loop;
}

void PolyRamp::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
   clockReset();
}

uint32_t PolyRamp::compileStageLength(const uint8_t& index) const
{
   if (0 == polyRampLength || 0 == stages.size())
      return 0;

   const bool isLastPolyRamp = (static_cast<uint64_t>(index + 1) >= stages.size());
   if (!isLastPolyRamp)
   {
      return stages[index].stageLength;
   }
   else
   {
      const uint32_t remainingSteps = polyRampLength - stepsTaken;
      return remainingSteps;
   }
}

#endif // PolyRampHPP
