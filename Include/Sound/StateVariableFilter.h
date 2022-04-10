#ifndef StateVariableFilterH
#define StateVariableFilterH

#include <Abstract/AbstractEffect.h>

// see https://en.wikipedia.org/wiki/State_variable_filter

class StateVariableFilter : public Abstract::Effect
{
public:
   inline StateVariableFilter();

public:
   inline void init(const float& sampleRate, const FilterMode& mode = FilterMode::LowPass);
   inline float changeSound(const float& in) override; // will return value according to set mode

   // individual outputs
   inline float lowPass() const;
   inline float bandPass() const;
   inline float highPass() const;
   inline float notch() const;

   inline void setFrequency(const float& newFrequency);
   inline void setResonance(const float& newResonannce);
   inline void setDrive(const float& newDrive);

private:
   struct Modes
   {
      float low = 0.0;
      float band = 0.0;
      float high = 0.0;
      float notch = 0.0;
   };

private:
   inline void process(const float& in);
   inline void compileDampening();

private:
   float sampleRate;
   FilterMode mode;
   float frequency;
   float resonance;
   float drive;

   // internal
   uint8_t numberOfPasses;
   float predrive;
   float dampening;
   Modes buffer;
   Modes output;
};

#ifndef StateVariableFilterHPP
#include "../../StateVariableFilter.hpp"
#endif // NOT StateVariableFilterHPP

#endif // NOT StateVariableFilterH
