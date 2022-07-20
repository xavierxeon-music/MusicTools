#ifndef SpectrumHPP
#define SpectrumHPP

#include <Sound/Spectrum.h>

Spectrum::Spectrum()
   : bufferSize(pow(2, Spectrum::frameSize))
   , transform()
   , buffer{}
   , writeIndex(0)
   , bufferReadIndex(0)
   , bufferWriteIndex(1)
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
   Data input = buffer[bufferReadIndex];
   Data output(bufferSize, 0.0);

   qDebug() << input[511] << input[520] << output[511] << output[520];

   transform.do_fft(input.data(), output.data());

   qDebug() << input[511] << input[520] << output[511] << output[520];

   return output;
}

#endif // NOT SpectrumHPP
