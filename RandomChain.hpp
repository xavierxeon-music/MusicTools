#ifndef RandomChainHPP
#define RandomChainHPP

#include <Blocks/RandomChain.h>

FastRandom RandomChain::generator(0);

RandomChain::RandomChain()
   : Abstract::Chain()
   , Remember::Container()
   , type(this, Type::Ramp)
   , minValue(this, 0)
   , maxValue(this, 255)
   , minDuration(this, 1)
   , maxDuration(this, 16)
   , link()
   , valueMapper(0, 1, minValue, maxValue)
   , durationMapper(0, 1, minDuration, maxDuration)
{
   rollDice();
   addLink(&link);
}

uint8_t RandomChain::getValue(const float& tickPercentage)
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

const RandomChain::Type& RandomChain::getType() const
{
   return type.constRef();
}

void RandomChain::setType(const Type& newType)
{
   type = newType;
   Remember::Root::setUnsynced();
}

const uint8_t& RandomChain::getMinValue() const
{
   return minValue.constRef();
}

void RandomChain::setMinValue(const uint8_t& newValue)
{
   minValue = newValue;
   valueMapper.setMinOutput(newValue);
   Remember::Root::setUnsynced();
}

const uint8_t& RandomChain::getMaxValue() const
{
   return maxValue.constRef();
}

void RandomChain::setMaxValue(const uint8_t& newValue)
{
   maxValue = newValue;
   valueMapper.setMaxOutput(newValue);
   Remember::Root::setUnsynced();
}

const Tempo::Tick& RandomChain::getMinDuration() const
{
   return minDuration.constRef();
}

void RandomChain::setMinDuration(const Tempo::Tick& newDuration)
{
   minDuration = newDuration;
   durationMapper.setMinOutput(newDuration);
   Remember::Root::setUnsynced();
}

const Tempo::Tick& RandomChain::getMaxDuration() const
{
   return maxDuration.constRef();
}

void RandomChain::setMaxDuration(const Tempo::Tick& newDuration)
{
   maxDuration = newDuration;
   durationMapper.setMaxOutput(newDuration);
   Remember::Root::setUnsynced();
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
   link.setLength(durationMapper(generator.value()));

   if (Type::Ramp == type)
   {
      link.startValue = valueMapper(value);
      link.endValue = valueMapper(generator.value());
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
