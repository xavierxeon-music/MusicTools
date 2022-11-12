#ifndef DelayLineHPP
#define DelayLineHPP

#include <Effect/DelayLine.h>

template <uint32_t MaxSamples>
DelayLine<MaxSamples>::DelayLine()
   : Abstract::Effect()
   , data()
   , delay(MaxSamples)
   , indexIn(0)
   , feedback(0.0)
   , feedbackEffect(nullptr)
   , feedfront(0.0)
   , feedfrontEffect(nullptr)
{
}

template <uint32_t MaxSamples>
float DelayLine<MaxSamples>::changeSound(const float& in)
{
   auto mix = [](const float& a, const float& b, const float& ratio)
   {
      const float apart = a * (1.0 - ratio);
      const float bpart = b * ratio;
      return apart + bpart;
   };

   const uint32_t indexOut = (indexIn + (MaxSamples - delay)) % MaxSamples;
   float out = data[indexOut];

   data[indexIn] = mix(in, feedbackEffect ? feedbackEffect->changeSound(out) : out, feedback);
   indexIn++;
   indexIn = (indexIn % MaxSamples);

   const float value = mix(out, feedfrontEffect ? feedfrontEffect->changeSound(in) : in, feedfront);
   return value;
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setDelay(const uint32_t& samples)
{
   if (samples < MaxSamples)
      delay = samples;
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setDelay(const float& delayTimeInMilliSeconds, const float& sampleRate)
{
   const uint32_t samples = static_cast<uint32_t>(delayTimeInMilliSeconds * (sampleRate / 1000.0));
   setDelay(samples);
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setFeedback(const float& factor)
{
   feedback = factor;
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setFeedbackEffect(Abstract::Effect* effect)
{
   feedbackEffect = effect;
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setFeedfront(const float& factor)
{
   feedfront = factor;
}

template <uint32_t MaxSamples>
void DelayLine<MaxSamples>::setFeedfrontEffect(Abstract::Effect* effect)
{
   feedfrontEffect = effect;
}

#endif // NOT DelayLineHPP
