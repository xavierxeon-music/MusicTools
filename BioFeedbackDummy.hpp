#ifndef BioFeedbackDummyHPP
#define BioFeedbackDummyHPP

#include <Blocks/BioFeedbackDummy.h>

#include <Tools/Range.h>

BioFeedbackDummy::BioFeedbackDummy(const float& sampleRate)
   : sawTable()
   , baseOscilator()
   , noiseGenerator()
   , noiseFilter()
   , signalFilter()
   , filterFrequencyMapper(0.0, 1.0, 10000.0, 10.0)
   , state()
   , modulationMap()
{
   for (const FunctionId& id : {BaseFrequency, BaseAmplitude, NoiseSmooth, NoiseAmplitude, MasterSmooth, MasterAmplitude})
   {
      state[id] = 0.0;
      modulationMap[id] = Modulation{0.0, 0.0};
   }
   state[BaseFrequency] = 50.0;
   state[BaseAmplitude] = 1.0;

   state[NoiseSmooth] = 0.0;
   state[NoiseAmplitude] = 1.0;

   state[MasterSmooth] = 0.0;
   state[MasterAmplitude] = 1.0;

   sawTable.setWaveform(Standard::Waveform::Saw);

   noiseFilter.setResonance(0.5);
   noiseFilter.setDrive(0.5);

   signalFilter.setResonance(1.0);
   signalFilter.setDrive(0.1);

   setSampleRate(sampleRate);
}

void BioFeedbackDummy::setSampleRate(const float& sampleRate)
{
   baseOscilator.init(&sawTable, sampleRate);
   noiseFilter.init(sampleRate);
   signalFilter.init(sampleRate);
}

float BioFeedbackDummy::compileSignalVoltage(float* baseSoundVoltage)
{
   auto stateValue = [&](const FunctionId& id) -> float
   {
      const Modulation& mod = modulationMap[id];
      return state[id] + mod.value * mod.strength;
   };

   const float frequency = stateValue(BaseFrequency);
   baseOscilator.setFrequency(frequency);
   const float baseValue = baseOscilator.createSound();
   if (baseSoundVoltage)
      *baseSoundVoltage = 10.0 * baseValue;

   float noiseValue = 2.0 * noiseGenerator.value() - 1.0;
   const float noiseSmooth = stateValue(NoiseSmooth);
   const float noiseSmoothFrequency = filterFrequencyMapper(noiseSmooth);
   noiseFilter.setFrequency(noiseSmoothFrequency);
   noiseValue = noiseFilter.changeSound(noiseValue);

   float value = (baseValue * stateValue(BaseAmplitude)) + (noiseValue * stateValue(NoiseAmplitude));

   const float masterSmooth = stateValue(MasterSmooth);
   const float masterSmoothFrequency = filterFrequencyMapper(masterSmooth);
   signalFilter.setFrequency(masterSmoothFrequency);
   value = signalFilter.changeSound(value);

   value = stateValue(MasterAmplitude) * value;

   return 10.0 * value;
}

void BioFeedbackDummy::setState(const FunctionId& id, const float& value)
{
   if (BaseFrequency == id)
      setBaseFrequency(value);
   else if (BaseAmplitude == id)
      setBaseMix(value);
   else if (NoiseSmooth == id)
      setNoiseSmoothness(value);
   else if (NoiseAmplitude == id)
      setNoiseMix(value);
   else if (MasterSmooth == id)
      setMasterSmoothness(value);
   else if (MasterAmplitude == id)
      setMasterVolume(value);
}

void BioFeedbackDummy::setModulation(const FunctionId& id, const float& value, const float& strength)
{
   modulationMap[id] = Modulation{value, strength};
}

void BioFeedbackDummy::setBaseFrequency(const float frequency)
{
   state[BaseFrequency] = frequency;
}

void BioFeedbackDummy::setBaseMix(const float& value)
{
   state[BaseAmplitude] = Range::clamp<float>(value, 0.0, 1.0);
}

void BioFeedbackDummy::setNoiseSmoothness(const float& value)
{
   state[NoiseSmooth] = Range::clamp<float>(value, 0.0, 1.0);
}

void BioFeedbackDummy::setNoiseMix(const float& value)
{
   state[NoiseAmplitude] = Range::clamp<float>(value, 0.0, 1.0);
}

void BioFeedbackDummy::setMasterSmoothness(const float& value)
{
   state[MasterSmooth] = Range::clamp<float>(value, 0.0, 1.0);
}

void BioFeedbackDummy::setMasterVolume(const float& value)
{
   state[MasterAmplitude] = Range::clamp<float>(value, 0.0, 1.0);
}

#endif // NOT BioFeedbackDummyHPP
