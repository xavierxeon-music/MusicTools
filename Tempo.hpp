#ifndef TempoHPP
#define TempoHPP

#include <Music/Tempo.h>

Tempo::Tempo()
   : runState(RunState::Reset)
   , bpm()
   , tickPercentage(0.0f)
{
}

std::string Tempo::getName(const Division& division)
{
   if (Division::Bar4 == division)
      return "4 bars";
   else if (Division::Bar2 == division)
      return "2 bars";
   else if (Division::Bar == division)
      return "bar";
   else if (Division::Quarter == division)
      return "quarter";
   else if (Division::Eigth == division)
      return "8th";
   else
      return "16th";
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

void TempoControl::advance(const float callackRate)
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
}

#endif // TempoHPP
