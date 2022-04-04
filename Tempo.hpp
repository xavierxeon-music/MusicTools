#ifndef TempoHPP
#define TempoHPP

#include <Music/Tempo.h>

Tempo::Tempo()
   : runState(RunState::Reset)
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
   // do nothing
   (void)division;
   return 0;
}

double Tempo::getPercentage(const Division& division) const
{
   // do nothing
   (void)division;
   return 0.0;
}

#endif // TempoHPP
