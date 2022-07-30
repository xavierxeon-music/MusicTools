#ifndef RevoiceHPP
#define RevoiceHPP

#include <Effect/Revoice.h>

Revoice::Revoice(const uint8_t& numberOfVocices)
   : Abstract::BufferedEffect(Spectrum::compileBufferSize())
   , numberOfVocices(numberOfVocices)
   , oscilators(nullptr)
   , sineTable()
   , sampleRate(1.0)
   , spectrum()
{
   oscilators = new WaveTable::Oscilator[numberOfVocices];

   sineTable.setWaveform(Standard::Waveform::Sine);

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
   {
      oscilators[voice].init(&sineTable, sampleRate);
      oscilators[voice].setAmplitude(1.0);
   }
}

Revoice::~Revoice()
{
   delete[] oscilators;
   oscilators = nullptr;
}

const uint8_t& Revoice::getNumberOfVoices() const
{
   return numberOfVocices;
}

void Revoice::setNumberOfVoices(const uint8_t& newNumberOfVocices)
{
   if (newNumberOfVocices == numberOfVocices)
      return;

   numberOfVocices = newNumberOfVocices;

   delete[] oscilators;
   oscilators = new WaveTable::Oscilator[numberOfVocices];

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
   {
      oscilators[voice].init(&sineTable, sampleRate);
      oscilators[voice].setAmplitude(1.0);
   }

   clear();
}

void Revoice::setSampleRate(const float& newSampleRate)
{
   sampleRate = newSampleRate;

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
      oscilators[voice].init(&sineTable, sampleRate);

   clear();
}

Data Revoice::convert(const Data& input)
{
   static const float maxAmplitude = 500 * numberOfVocices;
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

   for (uint8_t voice = 0; voice < numberOfVocices; voice++)
   {
      const float amplitude = amplitudeList.at(voice);
      const float frequency = amplitudeMap[amplitude];
      oscilators[voice].setFrequency(frequency);
   }

   Data sound(bufferSize, 0.0);
   for (uint16_t index = 0; index < bufferSize; index++)
   {
      float value = 0;
      for (uint8_t voice = 0; voice < numberOfVocices; voice++)
      {
         const float volume = amplitudeList.at(voice) / maxAmplitude;
         value += volume * oscilators[voice].createSound();
      }
      sound[index] = value;
   }
   return sound;
}

Data Revoice::proccessBuffer(const Data& input)
{
   return convert(input);
}

#endif // NOT RevoiceHPP
