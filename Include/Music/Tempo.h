#ifndef TempoH
#define TempoH

#include <MusicTools.h>

class Tempo
{
public:
   enum Division
   {
      Sixteenth = 1,
      Eigth = 2,
      Quarter = 4,
      Bar = 16
   };

   enum RunState
   {
      Reset,
      Off,
      FirstTick,
      Running
   };

public:
   inline Tempo();

public:
   inline static std::string getName(const Division& division);
   inline RunState getRunState() const;
   inline bool isRunningOrFirstTick() const;
   virtual uint8_t getBeatsPerMinute() const = 0;
   virtual inline uint8_t getCounter(const Division& division) const;
   virtual inline double getPercentage(const Division& division) const;

protected:
   RunState runState;
};

#ifndef TempoHPP
#include "../../Tempo.hpp"
#endif // NOT Tempo.hpp

#endif // NOT TempoH
