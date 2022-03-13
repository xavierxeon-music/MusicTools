#ifndef GraphHPP
#define GraphHPP

#include <Blocks/Graph.h>

#include <Tools/Variable.h>

// points

Graph::Stage::Stage(const uint8_t& startHeight, const uint8_t& length)
   : startHeight(this, startHeight)
   , length(this, length)
{
}

Graph::Stage::~Stage()
{
}

uint8_t Graph::Stage::getStartHeight() const
{
   return startHeight;
}

uint8_t Graph::Stage::getLength() const
{
   return length;
}

// graph

Graph::Graph()
   : stepSize(this, Tempo::Division::Bar)
   , length(this, 0)
   , stages(this)
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

void Graph::changeStepSize(bool longer)
{
   using StepSizeOrder = std::vector<Tempo::Division>;
   static const StepSizeOrder order = {Tempo::Division::Sixteenth, Tempo::Division::Eigth, Tempo::Division::Quarter, Tempo::Division::Bar};

   Variable::Enum<Tempo::Division> var(stepSize, order, true);

   var.change(longer);

   Remember::Root::setUnsynced();
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize));
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
