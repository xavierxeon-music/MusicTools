#ifndef GraphHPP
#define GraphHPP

#include <Blocks/Graph.h>

#include <Tools/Variable.h>

// points

Graph::Point::Point()
   : height(this, 0)
   , length(this, 0)
{
}

Graph::Point::~Point()
{
}

// graph

Graph::Graph()
   : stepSize(this, Tempo::Division::Bar)
   , pointList(this)
   , currentPointIndex(0)
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
   currentPointIndex = 0;

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
   return (0 != pointList.size());
}

#endif // GraphHPP
