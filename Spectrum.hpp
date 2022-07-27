#ifndef SpectrumHPP
#define SpectrumHPP

#include <Sound/Spectrum.h>

Spectrum::Spectrum()
   : bufferSize(Spectrum::compileBufferSize())
   , transform()
   , buffer{}
   , writeIndex(0)
   , bufferReadIndex(0)
   , bufferWriteIndex(1)
   , complexAmplitude(bufferSize, 0.0)
{
   buffer[0] = Data(bufferSize, 0.0);
   buffer[1] = Data(bufferSize, 0.0);
}

bool Spectrum::fill(const float& value)
{
   buffer[bufferWriteIndex][writeIndex] = value;
   writeIndex++;

   if (writeIndex < bufferSize)
      return false;

   writeIndex = 0;
   if (0 == bufferReadIndex)
   {
      bufferReadIndex = 1;
      bufferWriteIndex = 0;
   }
   else
   {
      bufferReadIndex = 0;
      bufferWriteIndex = 1;
   }

   return true;
}

Spectrum::Map Spectrum::analyse(const float& sampleRate)
{
   const Data& input = buffer[bufferReadIndex];
   transform.do_fft(complexAmplitude.data(), input.data());

   //return complexFrequency;

   const float binSize = sampleRate / bufferSize;
   const uint16_t halfBufferSize = bufferSize / 2;

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

#endif // NOT SpectrumHPP
