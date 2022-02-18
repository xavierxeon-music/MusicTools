#ifndef TrapezoidHPP
#define TrapezoidHPP

#include <Blocks/Trapezoid.h>

#include <map>

#include <Abstract/AbstractSettings.h>
#include <Tools/Variable.h>

Trapezoid::Trapezoid()
   : Remember::Container()
   , stages(this, {0, 0, 0, 0, 0})
   , bounds(this, {0.0, 1.0})
   , stepSize(this, Tempo::Division::Bar)
   , stage(Stage::Wait)
   , stepCounter(0)
   , indexCounter(0)
   , firstTick(false)
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
   stepCounter.setMaxValue(static_cast<uint8_t>(stepSize.constValue()));

   if (isValid())
   {
      uint32_t duration = getStageDuration();
      if (0 == duration)
         advanceToNextStage();
   }
   setIndexCounterLength();
}

void Trapezoid::clockTick()
{
   if (!isValid())
      return;

   if (firstTick) // ignore the first clock tick
   {
      firstTick = false;
      return;
   }

   if (stepCounter.nextAndIsMaxValue())
   {
      if (indexCounter.nextAndIsMaxValue())
      {
         advanceToNextStage();
         setIndexCounterLength();
      }
   }
}

void Trapezoid::clockReset()
{
   stepCounter.reset();
   indexCounter.reset();

   firstTick = true;
   stage = Stage::Wait;

   if (isValid())
   {
      uint32_t duration = getStageDuration();
      if (0 == duration)
         advanceToNextStage();
   }
   setIndexCounterLength();
}

const Trapezoid::Stage& Trapezoid::getCurrentStage() const
{
   return stage;
}

const uint8_t& Trapezoid::getLength(const Stage& stage) const
{
   const uint8_t index = static_cast<uint8_t>(stage);
   return stages[index].constValue();
}

void Trapezoid::changeLength(const Stage& stage, bool longer)
{
   const uint8_t index = static_cast<uint8_t>(stage);
   uint8_t& refValue = stages[index].refValue();

   Variable::Integer<uint8_t> var(refValue, 0, 255, true);
   var.change(longer);

   if (indexCounter.getCurrentValue() >= refValue)
      indexCounter.reset();

   indexCounter.setMaxValue(refValue);

   Abstract::Settings::invalidateSettings();
}

float Trapezoid::getCurrentStagePercentage() const
{
   if (!isValid())
      return 0.0;

   const float currentIndex = static_cast<float>(indexCounter.getCurrentValue());
   const float currentStep = static_cast<float>(stepCounter.getCurrentValue()) / static_cast<float>(stepCounter.getMaxValue());
   const float duration = static_cast<float>(getStageDuration());

   const float percentage = (currentStep + currentIndex) / duration;
   return percentage;
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

   Abstract::Settings::invalidateSettings();
   stepCounter.setMaxValue(static_cast<uint8_t>(stepSize.constValue()));
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

void Trapezoid::setIndexCounterLength()
{
   const uint8_t index = static_cast<uint8_t>(stage);
   const uint8_t value = stages[index].constValue();

   indexCounter.setMaxValue(value);
}

#endif // TrapezoidHPP
