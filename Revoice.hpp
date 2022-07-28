#ifndef RevoiceHPP
#define RevoiceHPP

#include <Effect/Revoice.h>

Revoice::Revoice()
   : Abstract::BufferedEffect(Spectrum::compileBufferSize())
   , oscilators{}
   , sineTable()
   , sampleRate(1.0)
   , spectrum()
{
   sineTable.setWaveform(Standard::Waveform::Sine);

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
   {
      oscilators[voice].init(&sineTable, sampleRate);
      oscilators[voice].setAmplitude(1.0);
   }
}

void Revoice::setSampleRate(const float& newSampleRate)
{
   sampleRate = newSampleRate;

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
      oscilators[voice].init(&sineTable, sampleRate);
}

Data Revoice::convert(const Data& input)
{
   static const float maxAmplitude = 1000 * numberOfVocices;
   static const uint16_t bufferSize = Spectrum::compileBufferSize();

   const Spectrum::Map spectrumMap = spectrum.analyse(input, sampleRate);

   AmplitudeMap amplitudeMap;
   Data amplitudeList;
   for (Spectrum::Map::const_iterator it = spectrumMap.cbegin(); it != spectrumMap.cend(); it++)
   {
      amplitudeMap[it->second] = it->first;
      amplitudeList.push_back(it->second);
   }

   std::sort(amplitudeList.begin(), amplitudeList.end(), std::greater<float>());

   Data sound;
   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
   {
      const float amplitude = amplitudeList.at(voice);
      const float frequency = amplitudeMap[amplitude];
      oscilators[voice].setFrequency(frequency);
   }

   for (uint16_t index = 0; index < bufferSize; index++)
   {
      float value = 0;
      for (uint8_t voice = 0; voice < numberOfVocices; voice++)
      {
         const float volume = amplitudeList.at(voice) / maxAmplitude;
         value += volume * oscilators[voice].createSound();
      }
      sound.push_back(value);
   }

   return sound;
}

Data Revoice::proccessBuffer(const Data& input)
{
   return convert(input);
}

#endif // NOT RevoiceHPP
