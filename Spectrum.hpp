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
   , complexFrequency(bufferSize, 0.0)
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

Data Spectrum::analyse()
{
   const Data& input = buffer[bufferReadIndex];
   transform.do_fft(complexFrequency.data(), input.data());

   //return complexFrequency;

   const uint16_t halfBufferSize = bufferSize / 2;
   Data frequency(halfBufferSize, 0.0);

   for (uint16_t index = 0; index < halfBufferSize; index++)
   {
      const float real = complexFrequency.at(index + 0);
      const float img = complexFrequency.at(index + halfBufferSize);
      const float absSquare = real * real + img * img;

      frequency[index] = sqrt(absSquare);
   }

   return frequency;
}

uint16_t Spectrum::compileBufferSize()
{
   return pow(2, frameSize);
}

#endif // NOT SpectrumHPP
