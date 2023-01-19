#ifndef ChainRandomHPP
#define ChainRandomHPP

#include <Blocks/ChainRandom.h>

ChainRandom::ChainRandom()
   : Abstract::Chain()
   , Remember::Container()
   , link()
   , currentBarDuration(0)
   , generator(0)
   , type(this, Type::Ramp)
   , minValue(this, 0)
   , maxValue(this, 255)
   , valueMapper(0, 1, minValue, maxValue)
   , minBarDuration(this, 1)
   , maxBarDuration(this, 16)
   , durationMapper(0, 1, minBarDuration, maxBarDuration)
{
   generator.reset(); // use random seed!

   rollDice();
   addLink(&link);
}

uint8_t ChainRandom::getValue(const float& tickPercentage) const
{
   if (!hasLinks())
      return 0;

   if (Type::Ramp == type)
   {
      const float linkPercentage = getCurrentLinkPrecentage(tickPercentage);
      const float diffValue = link.endValue - link.startValue;
      const uint8_t value = static_cast<uint8_t>(link.startValue + linkPercentage * diffValue);

      return value;
   }

   return link.startValue;
}

bool ChainRandom::isOn() const
{
   if (!hasLinks())
      return false;

   return (link.startValue >= 128);
}

uint8_t ChainRandom::linkStartValue() const
{
   if (!hasLinks())
      return 0;

   return link.startValue;
}

uint8_t ChainRandom::linkEndValue() const
{
   if (!hasLinks())
      return 0;

   return link.endValue;
}

const ChainRandom::Type& ChainRandom::getType() const
{
   return type.constRef();
}

void ChainRandom::setType(const Type& newType)
{
   type = newType;
   rollDice();
}

const uint8_t& ChainRandom::getMinValue() const
{
   return minValue.constRef();
}

bool ChainRandom::setMinValue(const uint8_t& newValue)
{
   if (newValue > maxValue)
      return false;

   minValue = newValue;
   valueMapper.setMinOutput(newValue);

   rollDice();
   return true;
}

const uint8_t& ChainRandom::getMaxValue() const
{
   return maxValue.constRef();
}

bool ChainRandom::setMaxValue(const uint8_t& newValue)
{
   if (newValue < minValue)
      return false;

   maxValue = newValue;
   valueMapper.setMaxOutput(newValue);

   rollDice();
   return true;
}

const Tempo::Tick& ChainRandom::getMinBarDuration() const
{
   return minBarDuration.constRef();
}

bool ChainRandom::setMinBarDuration(const Tempo::Tick& newDuration)
{
   if (newDuration > maxBarDuration)
      return false;

   minBarDuration = newDuration;
   durationMapper.setMinOutput(minBarDuration);
   debug() << __FUNCTION__ << newDuration;

   rollDice();
   return true;
}

const Tempo::Tick& ChainRandom::getMaxBarDuration() const
{
   return maxBarDuration.constRef();
}

bool ChainRandom::setMaxBarDuration(const Tempo::Tick& newDuration)
{
   if (newDuration < minBarDuration)
      return false;

   maxBarDuration = newDuration;
   durationMapper.setMaxOutput(maxBarDuration);

   rollDice();
   return true;
}

const Tempo::Tick& ChainRandom::getCurrentBarDuration() const
{
   return currentBarDuration;
}

void ChainRandom::postRead()
{
   valueMapper.setMinOutput(minValue);
   valueMapper.setMaxOutput(maxValue);

   durationMapper.setMinOutput(minBarDuration);
   durationMapper.setMaxOutput(maxBarDuration);

   rollDice();
}

void ChainRandom::linkDone(Abstract::Chain::Link* _link)
{
   (void)_link;

   rollDice();
   addLink(&link);
}

void ChainRandom::rollDice()
{
   const float value = generator.value();

   if (Type::Ramp == type)
   {
      link.startValue = link.endValue;
      link.endValue = valueMapper(value);
   }
   else if (Type::Steady == type)
   {
      link.startValue = valueMapper(value);
      link.endValue = link.startValue;
   }
   else if (Type::RndGate == type)
   {
      link.startValue = (value > 0.5) ? 255 : 0;
      link.endValue = link.startValue;
   }

   currentBarDuration = durationMapper(generator.value());
#ifndef FAST_TRACK
   link.setLength(16 * currentBarDuration);
#else
   link.setLength(currentBarDuration);
#endif // NOT FAST_TRACK
}

#endif // NOT ChainRandomHPP
