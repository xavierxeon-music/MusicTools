#ifndef TempoH
#define TempoH

#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

pyexport class Tempo
{
public:
   pyexport enum Division : uint8_t //
   {
      Sixteenth = 1,
      Eigth = 2,
      Quarter = 4,
      Bar = 16,
      Bar2 = 2 * Bar,
      Bar4 = 4 * Bar
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
   pyexport inline virtual double getPercentage() const;

protected:
   RunState runState;
   RingBuffer<uint16_t, 4 * 16> bpm;
   float tickPercentage;

private:
   friend class TempoControl;
};

pyexport class TempoControl : public Tempo
{
public:
   pyexport inline TempoControl();

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
