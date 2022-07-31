#include <Abstract/AbstractOscilator.h>

#include <Maths.h>
#include <MusicTools.h>

#include <Tools/Range.h>

Abstract::Oscilator::Oscilator()
   : frequency(110.0f)
   , amplitude(0.7f)

{
}

Abstract::Oscilator::~Oscilator()
{
}

void Abstract::Oscilator::setFrequency(const float& newFrequency)
{
   if (frequency == newFrequency)
      return;

   if (0.0f >= newFrequency)
      frequency = 0.0f;
   else
   {
#ifndef NON_DAISY_DEVICE
      // clamp to range of D/A converters
      // * 1.0 = amplitude ~0.5
      // * 2.0 = amplitude ~0.8
      // * 5.0 = full amplitude
      frequency = Range::clamp<float>(newFrequency, 2.0f, 20000.0f);
#else
      frequency = newFrequency;
#endif // NON_DAISY_DEVICE
   }
}

void Abstract::Oscilator::setCycleDuration(const float& cylceDuration)
{
   setFrequency(1.0 / cylceDuration);
}

const float& Abstract::Oscilator::getFrequency() const
{
   return frequency;
}

float Abstract::Oscilator::frequencyFromCV(float voltage)
{
   static const std::vector<float> noteAFreq = []()
   {
      float value = 0.25 * 55.0;

      std::vector<float> freq(11);
      freq[0] = value;

      for (uint8_t index = 1; index < 11; index++)
      {
         value *= 2;
         freq[index] = value;
      }
      return freq;
   }();

   if (0.0f > voltage || 10.0f < voltage)
      return 0.0f;

   // note A at 0.75 V, 1.75 V , etc
   // for octave = 0 note A is at 55 Hz, corresponding to -0.25 V

   const uint8_t octave = static_cast<uint8_t>(voltage + 0.25);
   const float rest = (voltage - octave) + 0.25;
   const float frequency = noteAFreq[octave] * pow(2, rest);

   return frequency;
}

void Abstract::Oscilator::setAmplitude(const float& newAmplitude)
{
   amplitude = newAmplitude;
}

const float& Abstract::Oscilator::getAmplitude() const
{
   return amplitude;
}
