#ifndef TempoH
#define TempoH

#include <limits>

#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

pyexport class Tempo
{
public:
   using Tick = uint16_t; // a sixteenth beat
   static constexpr Tick maxTick = std::numeric_limits<Tick>::max() - 1;

   pyexport enum Division : uint8_t //
   {
      Sixteenth = 1,
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
   inline Tempo(const Tempo& other);
   inline Tempo& operator=(const Tempo& other);

public:
   pyexport inline static std::string compileName(const uint8_t& division);
   pyexport inline RunState getRunState() const;
   pyexport inline bool isRunningOrFirstTick() const;
   pyexport inline virtual uint16_t getBeatsPerMinute() const;
   pyexport inline virtual float getPercentage() const; // from last tick

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
   pyexport inline virtual void advance(const float callackRate, const float allowedTickPercentage = 3.0); // to be called from loop
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
