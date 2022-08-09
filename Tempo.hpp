#ifndef TempoHPP
#define TempoHPP

#include <Music/Tempo.h>

Tempo::Tempo()
   : runState(RunState::Reset)
   , straightBarCount(16)
   , bpm()
   , msSinceLastTick(0.0f)
   , msPerTick(-1.0f)
   , tickPercentage(0.0f)
   , barCounter(0)
{
}

std::string Tempo::getName(const Division& division)
{
   if (Division::Bar == division)
      return "bar";
   else if (Division::Quarter == division)
      return "qtr";
   else if (Division::Eigth == division)
      return "8th";
   else
      return "16.";
}

Tempo::RunState Tempo::getRunState() const
{
   return runState;
}

bool Tempo::isRunningOrFirstTick() const
{
   if (RunState::FirstTick == runState)
      return true;

   if (RunState::Running == runState)
      return true;

   return false;
}

uint8_t Tempo::getCounter(const Division& division) const
{
   const uint8_t counter16 = static_cast<uint8_t>(straightBarCount.getCurrentValue());
   if (Division::Sixteenth == division)
   {
      return counter16;
   }
   else if (Division::Eigth == division)
   {
      const uint8_t overshoot = counter16 % 2;
      const uint8_t counter8 = (counter16 - overshoot) / 2;

      return counter8;
   }
   else if (Division::Quarter == division)
   {
      const uint8_t overshoot = counter16 % 4;
      const uint8_t counter4 = (counter16 - overshoot) / 4;

      return counter4;
   }
   return barCounter;
}

double Tempo::getPercentage(const Division& division) const
{
   const uint8_t counter16 = static_cast<uint8_t>(straightBarCount.getCurrentValue());
   if (Division::Sixteenth == division)
   {
      return tickPercentage;
   }
   else if (Division::Eigth == division)
   {
      const uint8_t overshoot = counter16 % 2;

      const double percentage = (static_cast<double>(overshoot) + tickPercentage) / 2.0;
      return percentage;
   }
   else if (Division::Quarter == division)
   {
      const uint8_t overshoot = counter16 % 4;

      const double percentage = (static_cast<double>(overshoot) + tickPercentage) / 4.0;
      return percentage;
   }
   else
   {
      const double percentage = (static_cast<double>(counter16) + tickPercentage) / 16.0;
      return percentage;
   }
   return 0.0;
}

uint16_t Tempo::getBeatsPerMinute() const
{
   return bpm;
}

void Tempo::advance(const float callackRate)
{
   if (!isRunningOrFirstTick())
      return;

   const float msCallBackIntervall = 1000.0f / callackRate;
   msSinceLastTick += msCallBackIntervall;

   if (msPerTick > 0.0)
      tickPercentage = msSinceLastTick / msPerTick;

   if (tickPercentage > 1.5)
      runState = RunState::Off;
}

void Tempo::clockTick()
{
   if (RunState::Reset == runState)
   {
      runState = RunState::FirstTick;
      return;
   }

   if (straightBarCount.nextAndIsMaxValue())
      barCounter++;

   runState = RunState::Running;

   msPerTick = msSinceLastTick;
   bpm += static_cast<uint8_t>(15000 / msSinceLastTick);
   msSinceLastTick = 0.0;
}

void Tempo::clockReset()
{
   straightBarCount.reset();

   bpm.clear();

   msSinceLastTick = 0.0;
   msPerTick = -1.0;
   tickPercentage = 0.0;

   runState = RunState::Reset;
   barCounter = 0;
}

#endif // TempoHPP
