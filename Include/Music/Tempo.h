#ifndef TempoH
#define TempoH

#include <MusicTools.h>
#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

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
   inline uint8_t getCounter(const Division& division) const;
   inline double getPercentage(const Division& division) const;
   inline uint8_t getBeatsPerMinute() const;
   // to control tempo
   inline virtual void advance(const float audioCallackRate); // to be called from audio loop
   inline void clockTick();
   inline void clockReset();

private:
   Counter straightBarCount; // 1 bar of 4/4
   RingBuffer<uint8_t, 16> bpm;
   float msSinceLastTick;
   float msPerTick;
   float tickPercentage;
   uint64_t barCounter;
   RunState runState;
};

#ifndef TempoHPP
#include "../../Tempo.hpp"
#endif // NOT Tempo.hpp

#endif // NOT TempoH
