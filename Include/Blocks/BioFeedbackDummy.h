#ifndef BioFeedbackDummyH
#define BioFeedbackDummyH

#include <Effect/StateVariableFilter.h>
#include <Sound/StandardTable.h>
#include <Sound/WaveTable.h>
#include <Sound/WaveTableOscilator.h>
#include <Tools/FastRandom.h>
#include <Tools/Range.h>

class BioFeedbackDummy
{
public:
   enum FunctionId : uint8_t //
   {
      BaseFrequency = 0,
      BaseAmplitude = 1,
      NoiseSmooth = 2,
      NoiseAmplitude = 3,
      MasterSmooth = 4,
      MasterAmplitude = 5
   };

public:
   inline BioFeedbackDummy(const float& sampleRate);

public:
   inline void setSampleRate(const float& sampleRate);

   inline float compileSignalVoltage(float* baseSoundVoltage = nullptr);
   inline void setState(const FunctionId& id, const float& value);                             // 0 to 1
   inline void setModulation(const FunctionId& id, const float& value, const float& strength); // value -1 to 1, strength 0 to 1

   inline void setBaseFrequency(const float frequency);
   inline void setBaseMix(const float& value);          // 0 to 1
   inline void setNoiseSmoothness(const float& value);  // 0 to 1
   inline void setNoiseMix(const float& value);         // 0 to 1
   inline void setMasterSmoothness(const float& value); // 0 to 1
   inline void setMasterVolume(const float& value);     // 0 to 1

private:
   struct Modulation
   {
      float value;
      float strength;

      using Map = std::map<FunctionId, Modulation>;
   };
   using State = std::map<FunctionId, float>;

private:
   Standard::Table sawTable;
   WaveTable::Oscilator baseOscilator;

   FastRandom noiseGenerator;
   StateVariableFilter noiseFilter;

   StateVariableFilter signalFilter;

   Range::Mapper filterFrequencyMapper;

   State state;
   Modulation::Map modulationMap;
};

#ifndef BioFeedbackDummyHPP
#include "../../BioFeedbackDummy.hpp"
#endif // NOT BioFeedbackDummyHPP

#endif // NOT BioFeedbackDummyH
