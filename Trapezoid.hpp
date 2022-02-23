#ifndef TrapezoidHPP
#define TrapezoidHPP

#include <Blocks/Trapezoid.h>

#include <map>

#include <Tools/Variable.h>

Trapezoid::Trapezoid()
   : Remember::Container()
   , stages(this, {0, 0, 0, 0, 0})
   , bounds(this, {0, 127})
   , stepSize(this, Tempo::Division::Bar)
   , stage(Stage::Wait)
   , stepSizeCounter(0)
   , stageLengthCounter(0)
   , firstTickDone(false)
{
}

std::string Trapezoid::stageName(const Stage& stage)
{
   if (Stage::Rise == stage)
      return "rise";
   else if (Stage::High == stage)
      return "high";
   else if (Stage::Fall == stage)
      return "fall";
   else if (Stage::Low == stage)
      return "low";
   else
      return "wait";
}

void Trapezoid::init()
{
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize.constValue()));

   if (isValid())
   {
      uint32_t duration = getStageDuration();
      if (0 == duration)
         advanceToNextStage();
   }
   setStageLengthCounterMaxValue();
}

void Trapezoid::clockTick()
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
         advanceToNextStage();
         setStageLengthCounterMaxValue();
      }
   }
}

void Trapezoid::clockReset()
{
   stepSizeCounter.reset();
   stageLengthCounter.reset();

   firstTickDone = false;
   stage = Stage::Wait;

   if (isValid())
   {
      uint32_t duration = getStageDuration();
      if (0 == duration)
         advanceToNextStage();
   }
   setStageLengthCounterMaxValue();
}

const Trapezoid::Stage& Trapezoid::getCurrentStage() const
{
   return stage;
}

float Trapezoid::getCurrentStagePercentage(const float& precentToNextTick) const
{
   if (!isValid())
      return 0.0;

   const float tickContribution = static_cast<float>(precentToNextTick + stepSizeCounter.getCurrentValue()) / static_cast<float>(stepSizeCounter.getMaxValue());
   const float stepContribution = static_cast<float>(stageLengthCounter.getCurrentValue());
   const float duration = static_cast<float>(getStageDuration());

   const float percentage = (tickContribution + stepContribution) / duration;
   return percentage;
}

float Trapezoid::getCurrentValue(const float& precentToNextTick) const
{
   const float min = getBound(Bound::Min);
   const float max = getBound(Bound::Max);

   const float percent = getCurrentStagePercentage(precentToNextTick);

   const float diff = (max - min) * percent;

   if (Stage::High == stage)
      return max;
   else if (Stage::Rise == stage)
   {
      const float value = min + diff;
      return value;
   }
   else if (Stage::Fall == stage)
   {
      const float value = max - diff;
      return value;
   }

   return min;
}

const uint8_t& Trapezoid::getStageLength(const Stage& stage) const
{
   const uint8_t index = static_cast<uint8_t>(stage);
   return stages[index].constValue();
}

void Trapezoid::changeStageLength(const Stage& stage, bool longer)
{
   const uint8_t index = static_cast<uint8_t>(stage);
   uint8_t& refValue = stages[index].refValue();

   Variable::Integer<uint8_t> var(refValue, 0, 255, true);
   var.change(longer);

   if (stageLengthCounter.getCurrentValue() >= refValue)
      stageLengthCounter.reset();

   stageLengthCounter.setMaxValue(refValue);

   Remember::Root::setUnsynced();
}

const Tempo::Division& Trapezoid::getStepSize() const
{
   return stepSize.constValue();
}

void Trapezoid::changeStepSize(bool longer)
{
   using StepSizeOrder = std::vector<Tempo::Division>;
   static const StepSizeOrder order = {Tempo::Division::Sixteenth, Tempo::Division::Eigth, Tempo::Division::Quarter, Tempo::Division::Bar};

   Variable::Enum<Tempo::Division> var(stepSize.refValue(), order, true);

   var.change(longer);

   Remember::Root::setUnsynced();
   stepSizeCounter.setMaxValue(static_cast<uint8_t>(stepSize.constValue()));
}

float Trapezoid::getBound(const Bound& bound) const
{
   const uint8_t index = (Bound::Min == bound) ? 0 : 1;
   const float value = static_cast<float>(bounds[index].constValue()) / 127.0;
   return value;
}

void Trapezoid::changeBound(const Bound& bound, bool more)
{
   if (Bound::Min == bound)
   {
      Variable::Integer<uint8_t> var(bounds[0].refValue(), 0, bounds[1].constValue(), false);
      if (var.change(more))
         Remember::Root::setUnsynced();
   }
   else
   {
      Variable::Integer<uint8_t> var(bounds[1].refValue(), bounds[0].constValue(), 127, false);
      if (var.change(more))
         Remember::Root::setUnsynced();
   }
}

bool Trapezoid::isValid() const
{
   uint32_t total = 0;
   for (uint8_t index = 0; index < 5; index++)
      total += stages[index].constValue();

   return (0 < total);
}

uint32_t Trapezoid::getStageDuration() const
{
   const uint8_t index = static_cast<uint8_t>(stage);
   const uint8_t value = stages[index].constValue();

   return value;
}

void Trapezoid::advanceToNextStage()
{
   auto advanceStage = [&]()
   {
      if (Stage::Wait == stage)
         stage = Stage::Rise;
      else if (Stage::Rise == stage)
         stage = Stage::High;
      else if (Stage::High == stage)
         stage = Stage::Fall;
      else if (Stage::Fall == stage)
         stage = Stage::Low;
      else if (Stage::Low == stage)
         stage = Stage::Rise;
   };

   uint32_t duration = 0;
   do
   {
      advanceStage();
      duration = getStageDuration();
   }
   while (0 == duration);
}

void Trapezoid::setStageLengthCounterMaxValue()
{
   const uint8_t index = static_cast<uint8_t>(stage);
   const uint8_t value = stages[index].constValue();

   stageLengthCounter.setMaxValue(value);
}

#endif // TrapezoidHPP
