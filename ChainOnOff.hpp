#ifndef ChainOnOffHPP
#define ChainOnOffHPP

#include <Blocks/ChainOnOff.h>

ChainOnOff::ChainOnOff()
   : Abstract::Chain()
   , Remember::Container()
   , link()
   , initialOn(this, true)
   , currentBarDuration(0)
   , generator()
   , minBarDurationOn(this, 1)
   , maxBarDurationOn(this, 16)
   , durationMapperOn(0, 1, minBarDurationOn, maxBarDurationOn)
   , minBarDurationOff(this, 1)
   , maxBarDurationOff(this, 16)
   , durationMapperOff(0, 1, minBarDurationOff, maxBarDurationOff)
{
   generator.reset(); // use random seed!

   link.on = !initialOn; // will be reversed in rollDice()
   rollDice();

   addLink(&link);
}

bool ChainOnOff::isOn() const
{
   return link.on;
}

const Tempo::Tick& ChainOnOff::getCurrentBarDuration() const
{
   return currentBarDuration;
}

bool ChainOnOff::getInitialOn() const
{
   return initialOn;
}

void ChainOnOff::setInitialOn(bool on)
{
   initialOn = on;
   rollDice();
}

const Tempo::Tick& ChainOnOff::getMinBarDurationOn() const
{
   return minBarDurationOn.constRef();
}

bool ChainOnOff::setMinBarDurationOn(const Tempo::Tick& value)
{
   if (value > maxBarDurationOn)
      return false;

   minBarDurationOn = value;
   durationMapperOn.setMinOutput(minBarDurationOn);

   rollDice();
   return true;
}

const Tempo::Tick& ChainOnOff::getMaxBarDurationOn() const
{
   return maxBarDurationOn.constRef();
}

bool ChainOnOff::setMaxBarDurationOn(const Tempo::Tick& value)
{
   if (value < minBarDurationOn)
      return false;

   maxBarDurationOn = value;
   durationMapperOn.setMaxOutput(maxBarDurationOn);

   rollDice();
   return true;
}

const Tempo::Tick& ChainOnOff::getMinBarDurationOff() const
{
   return minBarDurationOff.constRef();
}

bool ChainOnOff::setMinBarDurationOff(const Tempo::Tick& value)
{
   if (value > maxBarDurationOff)
      return false;

   minBarDurationOff = value;
   durationMapperOff.setMinOutput(minBarDurationOff);

   rollDice();
   return true;
}

const Tempo::Tick& ChainOnOff::getMaxBarDurationOff() const
{
   return maxBarDurationOff.constRef();
}

bool ChainOnOff::setMaxBarDurationOff(const Tempo::Tick& value)
{
   if (value < minBarDurationOff)
      return false;

   maxBarDurationOff = value;
   durationMapperOff.setMaxOutput(maxBarDurationOff);

   rollDice();
   return true;
}

void ChainOnOff::postRead()
{
   durationMapperOn.setMinOutput(minBarDurationOn);
   durationMapperOn.setMaxOutput(maxBarDurationOn);

   durationMapperOff.setMinOutput(minBarDurationOff);
   durationMapperOff.setMaxOutput(maxBarDurationOff);

   link.on = !initialOn; // will be reversed in rollDice()
   rollDice();
}

void ChainOnOff::linkDone(Abstract::Chain::Link* _link)
{
   (void)_link;

   rollDice();
   addLink(&link);
}

void ChainOnOff::rollDice()
{
   const float value = generator.value();
   if (link.on)
   {
      link.on = false;
      currentBarDuration = durationMapperOff(value);
   }
   else
   {
      link.on = true;
      currentBarDuration = durationMapperOn(value);
   }

#ifndef FAST_TRACK
   link.setLength(16 * currentBarDuration);
#else
   link.setLength(currentBarDuration);
#endif // NOT FAST_TRACK
}

#endif // NOT ChainOnOffHPP
