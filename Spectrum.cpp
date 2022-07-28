#include <Sound/Spectrum.h>

#include "ffft/FFTRealFixLen.h"

struct Spectrum::Internal
{
   ffft::FFTRealFixLen<frameSize> transform;
};

Spectrum::Spectrum()
   : internal(nullptr)
{
   internal = new Internal;
}

Spectrum::~Spectrum()
{
   delete internal;
   internal = nullptr;
}

Spectrum::Map Spectrum::analyse(const Data& data, const float& sampleRate)
{
   static Data complexAmplitude(compileBufferSize(), 0.0);
   internal->transform.do_fft(complexAmplitude.data(), data.data());

   const uint16_t bufferSize = compileBufferSize();
   const uint16_t halfBufferSize = bufferSize / 2;

   const float binSize = sampleRate / bufferSize;

   Map map;

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

uint16_t Spectrum::compileBufferSize()
{
   return pow(2, frameSize);
}
