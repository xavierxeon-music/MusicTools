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
   , startHeight(this, other.startHeight)
   , stageLength(this, other.stageLength)
{
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
   , length(this, 0)
   , stages(this)
   , loop(this, true)
   , currentStageIndex(0)
   , stepSizeCounter(0)
   , stageLengthCounter(0)
   , firstTickDone(false)
{
}

void Graph::init()
{
   stepSizeCounter.setMaxValue(static_cast<Tempo::Division>(stepSize));

   if (isValid())
   {
      // TODO points??
   }
}

void Graph::clockTick()
{
   if (!isValid())
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
         // TODO points??
      }
   }
}

void Graph::clockReset()
{
   stepSizeCounter.reset();
   stageLengthCounter.reset();

   firstTickDone = false;
   currentStageIndex = 0;

   if (isValid())
   {
      // TODO points??
   }
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
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize));
}

uint32_t Graph::getLength() const
{
   return length;
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

   LengthStatus result = (length == newLength) ? LengthStatus::Kept : LengthStatus::Changed;
   if (autoDiscard)
   {
      length = newLength;
      while (cutoffIndex < stages.size())
      {
         stages.remove(cutoffIndex);
      }
   }
   else
   {
      if (cutoffIndex > stages.size())
         return LengthStatus::Error;

      length = newLength;
   }

   Remember::Root::setUnsynced();
   return result;
}

void Graph::trimLength()
{
   uint32_t newLength = 0;
   for (uint8_t index = 0; index < stages.size(); index++)
      newLength += stages[index].stageLength;

   length = newLength;
   Remember::Root::setUnsynced();
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
}

void Graph::removeStage(const uint8_t& index)
{
   stages.remove(index);
   Remember::Root::setUnsynced();
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

   if (!expandLength && newLength > length)
      return LengthStatus::Error;

   stages[index].stageLength = stageLength;
   length = newLength;

   Remember::Root::setUnsynced();
   return LengthStatus::Changed;
}

uint8_t Graph::getCurrentStageIndex() const
{
   return currentStageIndex;
}

float Graph::getCurrentStagePercentage(const float& precentToNextTick) const
{
   (void)precentToNextTick;
   return 0.0;
}

float Graph::getCurrentValue(const float& precentToNextTick) const
{
   (void)precentToNextTick;
   return 0.0;
}

bool Graph::isLooping() const
{
   return loop;
}

void Graph::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
}

bool Graph::isValid() const
{
   if (0 == stages.size())
      return false;

   if (0 == length)
      return false;

   return true;
}

#endif // GraphHPP
