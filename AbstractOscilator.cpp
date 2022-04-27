#include <Abstract/AbstractOscilator.h>

#include <Maths.h>
#include <MusicTools.h>

Abstract::Oscilator::Oscilator()
{
}

Abstract::Oscilator::~Oscilator()
{
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
