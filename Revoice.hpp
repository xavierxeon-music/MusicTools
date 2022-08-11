#ifndef RevoiceHPP
#define RevoiceHPP

#include <algorithm>

#include <Effect/Revoice.h>

Revoice::Revoice(const uint8_t& numberOfVocices, const Spectrum::Quality& quality)
#ifdef NON_DAIS_DEVICE
   : Abstract::ThreadeBufferEffect(Spectrum::compileBufferSize(quality))
#else
   : Abstract::BufferedEffect(Spectrum::compileBufferSize(quality))
#endif
   , numberOfVocices(numberOfVocices)
   , oscilators(nullptr)
   , sineTable()
   , sampleRate(1.0)
   , spectrum(quality)
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
   if (0 < newNumberOfVocices)
      oscilators = new WaveTable::Oscilator[numberOfVocices];
   else
      oscilators = nullptr;

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
   if (0 == numberOfVocices)
      return input;

   using LoudnessMap = std::map<Spectrum::Quality, uint16_t>;
   static const LoudnessMap loudnessMap = {{Spectrum::Quality::Low, 100}, {Spectrum::Quality::Medium, 200}, {Spectrum::Quality::High, 300}, {Spectrum::Quality::Ultra, 400}};

   static const float scale = loudnessMap.at(spectrum.getQuality()) * numberOfVocices;
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

   Data sound(getBufferSize(), 0.0);
   for (uint16_t index = 0; index < getBufferSize(); index++)
   {
      float value = 0;
      for (uint8_t voice = 0; voice < numberOfVocices; voice++)
      {
         const float volume = amplitudeList.at(voice) / scale;
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
