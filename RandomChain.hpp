#ifndef RandomChainHPP
#define RandomChainHPP

#include <Blocks/RandomChain.h>

RandomChain::RandomChain()
   : Abstract::Chain()
   , Remember::Container()
   , type(this, Type::Ramp)
   , minValue(this, 0)
   , maxValue(this, 255)
   , minBarDuration(this, 1)
   , maxBarDuration(this, 16)
   , link()
   , valueMapper(0, 1, minValue, maxValue)
   , durationMapper(0, 1, minBarDuration, maxBarDuration)
   , currentBarDuration(0)
   , generator(0)
{
   generator.reset(); // use random seed!

   rollDice();
   addLink(&link);
}

uint8_t RandomChain::getValue(const float& tickPercentage) const
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

bool RandomChain::isOn() const
{
   if (!hasLinks())
      return false;

   return (link.startValue > 128);
}

uint8_t RandomChain::linkStartValue() const
{
   if (!hasLinks())
      return 0;

   return link.startValue;
}

uint8_t RandomChain::linkEndValue() const
{
   if (!hasLinks())
      return 0;

   return link.endValue;
}

const RandomChain::Type& RandomChain::getType() const
{
   return type.constRef();
}

void RandomChain::setType(const Type& newType)
{
   type = newType;
}

const uint8_t& RandomChain::getMinValue() const
{
   return minValue.constRef();
}

bool RandomChain::setMinValue(const uint8_t& newValue)
{
   if (newValue > maxValue)
      return false;

   minValue = newValue;
   valueMapper.setMinOutput(newValue);

   return true;
}

void RandomChain::changeMinValue(bool up)
{
   bool changed = false;

   if (up && minValue < 255)
      changed = setMinValue(minValue + 1);
   else if (!up and minValue > 0)
      changed = setMinValue(minValue - 1);

   if (changed)
      Remember::Root::setUnsynced();
}

const uint8_t& RandomChain::getMaxValue() const
{
   return maxValue.constRef();
}

bool RandomChain::setMaxValue(const uint8_t& newValue)
{
   if (newValue < minValue)
      return false;

   maxValue = newValue;
   valueMapper.setMaxOutput(newValue);

   return true;
}

void RandomChain::changeMaxValue(bool up)
{
   bool changed = false;

   if (up && maxValue < 255)
      changed = setMaxValue(maxValue + 1);
   else if (!up and maxValue > 0)
      changed = setMaxValue(maxValue - 1);

   if (changed)
      Remember::Root::setUnsynced();
}

const Tempo::Tick& RandomChain::getMinBarDuration() const
{
   return minBarDuration.constRef();
}

bool RandomChain::setMinBarDuration(const Tempo::Tick& newDuration)
{
   if (newDuration > maxBarDuration)
      return false;

   minBarDuration = newDuration;
   durationMapper.setMinOutput(minBarDuration);

   return true;
}

void RandomChain::changeMinBarDuration(bool up)
{
   bool changed = false;

   if (up && minBarDuration < 255 * 255)
      changed = setMinBarDuration(minBarDuration + 1);
   else if (!up and minBarDuration > 0)
      changed = setMinBarDuration(minBarDuration - 1);

   if (changed)
      Remember::Root::setUnsynced();
}

const Tempo::Tick& RandomChain::getMaxBarDuration() const
{
   return maxBarDuration.constRef();
}

bool RandomChain::setMaxBarDuration(const Tempo::Tick& newDuration)
{
   if (newDuration < minBarDuration)
      return false;

   maxBarDuration = newDuration;
   durationMapper.setMaxOutput(maxBarDuration);

   return true;
}

void RandomChain::changeMaxBarDuration(bool up)
{
   bool changed = false;

   if (up && maxBarDuration < 255 * 255)
      changed = setMaxBarDuration(maxBarDuration + 1);
   else if (!up and maxBarDuration > 0)
      changed = setMaxBarDuration(maxBarDuration - 1);

   if (changed)
      Remember::Root::setUnsynced();
}

const Tempo::Tick& RandomChain::getCurrentBarDuration() const
{
   return currentBarDuration;
}

void RandomChain::linkDone(Abstract::Chain::Link* _link)
{
   (void)_link;

   rollDice();
   addLink(&link);
}

void RandomChain::rollDice()
{
   const float value = generator.value();
   currentBarDuration = durationMapper(generator.value());
   link.setLength(16 * currentBarDuration);
   //link.setLength(currentBarDuration);

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
   else if (Type::Gate == type)
   {
      link.startValue = (value > 0.5) ? 255 : 0;
      link.endValue = link.startValue;
   }
}

#endif // NOT RandomChainHPP
