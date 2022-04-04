#ifndef TriggerdTempoH
#define TriggerdTempoH

#include <Music/Tempo.h>

#include <Tools/Counter.h>
#include <Tools/RingBuffer.h>

// expects 4PPQ, i.e. a clock tick every 16th step
class TriggerdTempo : public Tempo
{
public:
   inline TriggerdTempo();

public:
   inline uint8_t getCounter(const Division& division) const override;
   inline uint8_t getBeatsPerMinute() const override;
   inline double getPercentage(const Division& division) const override;
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
};

#ifndef TriggerdTempoHPP
#include "../../TriggerdTempo.hpp"
#endif // NOT TriggerdTempoHPP

#endif // NOT TriggerdTempoH
