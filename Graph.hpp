#ifndef GraphHPP
#define GraphHPP

#include <Blocks/Graph.h>

#include <Tools/Variable.h>

// stage

Graph::Stage::Stage(const uint8_t& startHeight, const uint8_t& stageLength)
   : Remember::Container()
   , startHeight(this, startHeight)
   , stageLength(this, stageLength)
{
}

Graph::Stage::Stage(const Stage& other)
   : Remember::Container()
   , startHeight(this, 0)
   , stageLength(this, 0)
{
   *this = other;
}

Graph::Stage::~Stage()
{
   // NEED virtual destructor, else compiler warning!
}

Graph::Stage& Graph::Stage::operator=(const Stage& other)
{
   startHeight = other.startHeight;
   stageLength = other.stageLength;

   return *this;
}

// graph

Graph::Graph()
   : Remember::Container()
   , stepSize(this, Tempo::Division::Bar)
   , graphLength(this, 0)
   , stages(this)
   , loop(this, true)
   , pastLoop(false)
   , currentStageIndex(0)
   , stepSizeCounter(0)
   , stepsTaken(0)
   , stageLengthCounter(0)
   , firstTickDone(false)
{
}

void Graph::clockTick()
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

void Graph::clockReset()
{
   stepSizeCounter.reset();
   stageLengthCounter.reset();

   stepSizeCounter.setMaxValue(static_cast<Tempo::Division>(stepSize));
   stageLengthCounter.setMaxValue(compileStageLength(0));

   firstTickDone = false;
   currentStageIndex = 0;
   stepsTaken = 0;
   pastLoop = false;
}

uint8_t Graph::getCurrentStageIndex() const
{
   return currentStageIndex;
}

float Graph::getCurrentStagePercentage(const float& precentToNextTick) const
{
   if (!isValid())
      return 0.0;

   const float tickContribution = static_cast<float>(precentToNextTick + stepSizeCounter.getCurrentValue()) / static_cast<float>(stepSizeCounter.getMaxValue());
   const float stepContribution = static_cast<float>(stageLengthCounter.getCurrentValue());
   const float duration = static_cast<float>(compileStageLength(currentStageIndex));

   const float percentage = (tickContribution + stepContribution) / duration;
   return percentage;
}

float Graph::getCurrentValue(const float& precentToNextTick) const
{
   if (!isValid() || pastLoop)
      return 0.0;

   const float startValue = stages[currentStageIndex].startHeight;
   const bool isLastStage = (currentStageIndex + 1 >= stages.size());
   const float endValue = isLastStage ? stages[0].startHeight : stages[currentStageIndex + 1].startHeight;

   const float percentage = getCurrentStagePercentage(precentToNextTick);
   const float diffValue = percentage * (endValue - startValue);

   const float value = startValue + diffValue;
   return value;
}

bool Graph::isValid() const
{
   if (0 == stages.size())
      return false;

   if (0 == graphLength)
      return false;

   return true;
}

Tempo::Division Graph::getStepSize() const
{
   return stepSize;
}

void Graph::setStepSize(const Tempo::Division& newStepSize)
{
   stepSize = newStepSize;
   Remember::Root::setUnsynced();
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize));
}

void Graph::changeStepSize(bool longer)
{
   using StepSizeOrder = std::vector<Tempo::Division>;
   static const StepSizeOrder order = {Tempo::Division::Sixteenth, Tempo::Division::Eigth, Tempo::Division::Quarter, Tempo::Division::Bar};

   Variable::Enum<Tempo::Division> var(stepSize, order, true);

   var.change(longer);

   Remember::Root::setUnsynced();
   clockReset();
}

uint32_t Graph::getLength() const
{
   return graphLength;
}

Graph::LengthStatus Graph::setLength(const uint32_t newLength, bool autoDiscard)
{
   uint8_t cutoffIndex = 0;
   uint32_t testLength = 0;
   for (uint8_t index = 0; index < stages.size(); index++)
   {
      testLength += stages[index].stageLength;
      if (testLength >= newLength)
         break;
      cutoffIndex = index;
   }

   LengthStatus result = (graphLength == newLength) ? LengthStatus::Kept : LengthStatus::Changed;
   if (autoDiscard)
   {
      graphLength = newLength;
      while (cutoffIndex < stages.size())
      {
         stages.remove(cutoffIndex);
      }
   }
   else
   {
      if (cutoffIndex > stages.size())
         return LengthStatus::Error;

      graphLength = newLength;
   }

   Remember::Root::setUnsynced();
   clockReset();
   return result;
}

void Graph::trimLength()
{
   uint32_t newLength = 0;
   for (uint8_t index = 0; index < stages.size(); index++)
      newLength += stages[index].stageLength;

   graphLength = newLength;

   Remember::Root::setUnsynced();
   clockReset();
}

uint8_t Graph::stageCount() const
{
   return stages.size();
}

Graph::LengthStatus Graph::addStage(const uint8_t& afterIndex)
{
   if (255 == stages.size())
      return LengthStatus::Error;

   Stage stage;
   stages.insert(stage, afterIndex + 1);

   Remember::Root::setUnsynced();
   clockReset();
   return LengthStatus::Kept;
}

void Graph::moveStage(const uint8_t& fromIndex, const uint8_t& toIndex)
{
   if (fromIndex == toIndex)
      return;

   Stage stageCopy = stages[fromIndex];

   stages.remove(fromIndex);
   stages.insert(stageCopy, toIndex);

   Remember::Root::setUnsynced();
   clockReset();
}

void Graph::removeStage(const uint8_t& index)
{
   stages.remove(index);
   Remember::Root::setUnsynced();
   clockReset();
}

uint8_t Graph::getStageStartHeight(const uint8_t& index)
{
   return stages[index].startHeight;
}

void Graph::setStageStartHeight(const uint8_t& index, const uint8_t& startHeight)
{
   stages[index].startHeight = startHeight;
   Remember::Root::setUnsynced();
}

uint8_t Graph::getStageLength(const uint8_t& index)
{
   return stages[index].stageLength;
}

Graph::LengthStatus Graph::setStageLength(const uint8_t& index, const uint8_t& stageLength, bool expandLength)
{
   uint32_t newLength = stageLength;
   for (uint8_t stageIndex = 0; stageIndex < stages.size(); stageIndex++)
   {
      if (index == stageIndex)
         continue;
      newLength += stages[stageIndex].stageLength;
   }

   if (!expandLength && newLength > graphLength)
      return LengthStatus::Error;

   stages[index].stageLength = stageLength;
   graphLength = newLength;

   Remember::Root::setUnsynced();
   clockReset();
   return LengthStatus::Changed;
}

bool Graph::isLooping() const
{
   return loop;
}

void Graph::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
   clockReset();
}

uint32_t Graph::compileStageLength(const uint8_t& index) const
{
   if (0 == graphLength || 0 == stages.size())
      return 0;

   const bool isLastStage = (index + 1 >= stages.size());
   if (!isLastStage)
   {
      return stages[index].stageLength;
   }
   else
   {
      const uint32_t remainingSteps = graphLength - stepsTaken;
      return remainingSteps;
   }
}

#endif // GraphHPP
