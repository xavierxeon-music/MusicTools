#ifndef TempoHPP
#define TempoHPP

#include <Music/Tempo.h>

#include <Music/TimeCode.h>

Tempo::Tempo()
   : runState(RunState::Reset)
   , bpm()
   , tickPercentage(0.0f)
{
}

Tempo::Tempo(const Tempo& other)
   : Tempo()
{
   *this = other;
}

Tempo& Tempo::operator=(const Tempo& other)
{
   runState = other.runState;
   bpm = other.bpm;
   tickPercentage = other.tickPercentage;

   return *this;
}

std::string Tempo::compileName(const uint8_t& division)
{
   if (0 == division)
      return "none";
   else if (Bar == division)
      return "bar";
   else if (Quarter == division)
      return "quarter";
   else if (Sixteenth == division)
      return "16th";

   TimeCode timeCode(division);
   std::string name;

   if (1 == timeCode.bar)
      name += "1 bar";
   else if (1 < timeCode.bar)
      name += std::to_string(timeCode.bar) + " bars";

   if (!name.empty() && 0 != timeCode.quarter)
      name += ", ";

   if (1 == timeCode.quarter)
      name += "1 quarter";
   else if (1 < timeCode.quarter)
      name += std::to_string(timeCode.quarter) + " quarters";

   if (!name.empty() && 0 != timeCode.tick)
      name += ", ";

   if (1 == timeCode.tick)
      name += "1 tick";
   else if (1 < timeCode.tick)
      name += std::to_string(timeCode.tick) + " ticks";

   return name;
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

double Tempo::getPercentage() const
{
   return tickPercentage;
}

uint16_t Tempo::getBeatsPerMinute() const
{
   return bpm;
}

// control

TempoControl::TempoControl()
   : Tempo()
   , msSinceLastTick(0.0f)
   , msPerTick(-1.0f)
{
}

void TempoControl::advance(const float callackRate, const float allowedTickPercentage)
{
   if (!isRunningOrFirstTick())
      return;

   const float msCallBackIntervall = 1000.0f / callackRate;
   msSinceLastTick += msCallBackIntervall;

   if (msPerTick > 0.0)
      tickPercentage = msSinceLastTick / msPerTick;

   if (tickPercentage > allowedTickPercentage)
      runState = RunState::Off;
}

void TempoControl::clockTick()
{
   if (RunState::Reset == runState)
   {
      runState = RunState::FirstTick;
      return;
   }

   runState = RunState::Running;

   msPerTick = msSinceLastTick;
   bpm += static_cast<uint8_t>(15000 / msSinceLastTick);
   msSinceLastTick = 0.0;
}

void TempoControl::clockReset()
{
   bpm.clear();

   msSinceLastTick = 0.0;
   msPerTick = -1.0;
   tickPercentage = 0.0;

   runState = RunState::Reset;
   debug() << __FUNCTION__;
}

#endif // TempoHPP
