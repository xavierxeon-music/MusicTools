#ifndef TempoH
#define TempoH

#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

pyexport class Tempo
{
public:
   class Control;

   pyexport enum Division //
   {
      Sixteenth = 1,
      Eigth = 2,
      Quarter = 4,
      Bar = 16
   };

   pyexport enum RunState //
   {
      Reset,
      Off,
      FirstTick,
      Running
   };

public:
   pyexport inline Tempo();

public:
   pyexport inline static std::string getName(const Division& division);
   pyexport inline RunState getRunState() const;
   pyexport inline bool isRunningOrFirstTick() const;
   pyexport inline virtual uint16_t getBeatsPerMinute() const;
   pyexport inline virtual uint8_t getCounter(const Division& division) const;
   pyexport inline virtual double getPercentage(const Division& division) const;


protected:
   RunState runState;
   Counter straightBarCount; // 1 bar of 4/4
   RingBuffer<uint16_t, 4 * 16> bpm;
   float tickPercentage;
   uint64_t barCounter;
};

pyexport class Tempo::Control : public Tempo
{
public:
   pyexport inline Control();

public:
   // to control tempo
   pyexport inline virtual void advance(const float callackRate); // to be called from loop
   pyexport inline void clockTick();
   pyexport inline void clockReset();

private:
   float msSinceLastTick;
   float msPerTick;
};

#ifndef TempoHPP
#include "../../Tempo.hpp"
#endif // NOT Tempo.hpp

#endif // NOT TempoH
