#ifndef StateVariableFilterHPP
#define StateVariableFilterHPP

#include <Effect/StateVariableFilter.h>

#include <Maths.h>
#include <Tools/Range.h>

StateVariableFilter::StateVariableFilter()
   : Abstract::Effect()
   , sampleRate(41000)
   , mode(FilterMode::LowPass)
   , sampleFrequency(0.25)
   , resonance(0.5)
   , drive(0.5)
   , numberOfPasses(2)
   , predrive(0.5)
   , dampening(0.0)
   , buffer()
   , output()
{
}

void StateVariableFilter::init(const float& _sampleRate, const FilterMode& _mode)
{
   sampleRate = _sampleRate;
   mode = _mode;
}

float StateVariableFilter::changeSound(const float& in)
{
   process(in);

   if (FilterMode::LowPass == mode)
      return lowPass();
   else if (FilterMode::BandPass == mode)
      return bandPass();
   else if (FilterMode::HighPass == mode)
      return highPass();
   else if (FilterMode::Notch == mode)
      return notch();
   else if (FilterMode::Peak == mode)
      return peak();

   return in;
}

float StateVariableFilter::lowPass() const
{
   return output.low;
}

float StateVariableFilter::bandPass() const
{
   return output.band;
}

float StateVariableFilter::highPass() const
{
   return output.high;
}

float StateVariableFilter::notch() const
{
   return output.notch;
}

float StateVariableFilter::peak() const
{
   return output.peak;
}

void StateVariableFilter::setFrequency(const float& newFrequency)
{
   const float clampedFrequency = Range::clamp<float>(newFrequency, 1.0e-6, sampleRate / 3.f);

   const float calcSampleFrequency = clampedFrequency / (sampleRate * numberOfPasses);
   sampleFrequency = 2.0f * std::sin(Maths::pi * Range::min<float>(0.25f, calcSampleFrequency));

   compileDampening();
}

void StateVariableFilter::setResonance(const float& newResonannce)
{
   resonance = Range::clamp<float>(newResonannce, 0.0, 1.0);
   drive = predrive * resonance;

   compileDampening();
}

void StateVariableFilter::setDrive(const float& newDrive)
{
   predrive = 1.0 - Range::clamp<float>(newDrive, 0.f, 1.f);
   drive = predrive * resonance;
}

void StateVariableFilter::process(const float& in)
{
   output = Modes(); // set all to zero

   auto singlePass = [&]()
   {
      buffer.notch = in - (dampening * buffer.band);
      buffer.low = buffer.low + (sampleFrequency * buffer.band);
      buffer.high = buffer.notch - buffer.low;
      buffer.band = (sampleFrequency * buffer.high) + buffer.band - (drive * buffer.band * buffer.band * buffer.band);
      buffer.peak = 0.0;

      output.low += 0.5f * buffer.low;
      output.band += 0.5f * buffer.band;
      output.high += 0.5f * buffer.high;
      output.notch += 0.5f * buffer.notch;
      output.peak += 0.5f * (buffer.low - buffer.high);
   };

   for (uint8_t index = 0; index < numberOfPasses; index++)
      singlePass();
}

void StateVariableFilter::compileDampening()
{
   const float d1 = 2.0f * (1.0f - powf(resonance, 0.25f));
   const float d2 = Range::min<float>(2.0f, 2.0f / sampleFrequency - sampleFrequency * 0.5f);
   dampening = Range::min<float>(d1, d2);
}

#endif // NOT StateVariableFilterHPP
