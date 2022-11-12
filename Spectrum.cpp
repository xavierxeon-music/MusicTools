#include <Utility/Spectrum.h>

#include "_fourier/FFTRealFixLen.h"

Spectrum::Spectrum(const Quality& quality)
   : quality(quality)
   , bufferSize(compileBufferSize(quality))
   , halfBufferSize(bufferSize / 2)
   , complexAmplitude(bufferSize, 0.0)
   , transform(nullptr)

{
   init();
}

Spectrum::~Spectrum()
{
   clear();
}

const Spectrum::Quality& Spectrum::getQuality() const
{
   return quality;
}

Spectrum::Map Spectrum::analyse(const Data& data, const float& sampleRate)
{
   if (bufferSize != data.size())
      return Map();

   transform->timeToFrequency(data, complexAmplitude);

   Map map;

   const float binSize = sampleRate / bufferSize;
   for (uint16_t index = 0; index < halfBufferSize; index++)
   {
      const float real = complexAmplitude.at(index + 0);
      const float img = complexAmplitude.at(index + halfBufferSize);
      const float absSquare = real * real + img * img;

      const float frequency = index * binSize;
      const float amplitude = sqrt(absSquare);

      map[frequency] = amplitude;
   }

   return map;
}

uint16_t Spectrum::compileBufferSize(const Quality& quality)
{
   return pow(2, static_cast<uint8_t>(quality));
}

void Spectrum::init()
{
   clear();

   if (Quality::Low == quality)
      transform = new ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Low)>();
   else if (Quality::Medium == quality)
      transform = new ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Medium)>();
   else if (Quality::High == quality)
      transform = new ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::High)>();
   else if (Quality::Ultra == quality)
      transform = new ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Ultra)>();
}

void Spectrum::clear()
{
   if (transform)
   {
      delete transform;
      transform = nullptr;
   }
}
