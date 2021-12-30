#ifndef TableOscilatorH
#define TableOscilatorH

#include <Abstract/AbstractOscilator.h>

class CircularTable;

// turns a CicularTable into an oscilator

// On Daisy device the frequency range is 2Hz to 20,000 Hz, otherwise any positive number
// A frequency of zero will turn off the oscilaotr.
// Amplitude should be between 0 and 1.

class TableOscilator : public Abstract::Oscilator
{
public:
   inline TableOscilator();

public:
   inline void init(const CircularTable* newTable, const float& newSampleRate);

   inline void setPhase(const float& newPhase);
   inline const float& getPhase() const;

   inline void setFrequency(const float& newFrequency);
   inline const float& getFrequency() const;

   inline void setAmplitude(const float& newAmplitude);
   inline const float& getAmplitude() const;

   inline float createSound() override;
   inline static float frequencyFromCV(float cv);

private:
   inline void compileDeltaPhase();

private:
   const CircularTable* table;
   float sampleRate;
   float phase;
   float frequency;
   float amplitude;
   float deltaPhase;
};

#include <TableOscilator.hpp>

#endif // TableOscilatorH
