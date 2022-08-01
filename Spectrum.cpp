#include <Sound/Spectrum.h>

#include "ffft/FFTRealFixLen.h"

class Spectrum::Internal
{
public:
   Internal(Spectrum* spectrum)
      : spectrum(spectrum)
   {
      if (Quality::Low == spectrum->quality)
         transformLow = new TransformLow();
      else if (Quality::Medium == spectrum->quality)
         transformMedium = new TransformMedium();
      else if (Quality::High == spectrum->quality)
         transformHigh = new TransformHigh();
      else if (Quality::Ultra == spectrum->quality)
         transformUltra = new TransformUltra();
   }

   ~Internal()
   {
      if (transformLow)
         delete transformLow, transformLow = nullptr;

      if (transformMedium)
         delete transformMedium, transformMedium = nullptr;

      if (transformHigh)
         delete transformHigh, transformHigh = nullptr;

      if (transformUltra)
         delete transformUltra, transformUltra = nullptr;
   }

   void fo_fft(const Data& input, Data& output)
   {
      if (Quality::Low == spectrum->quality)
         transformLow->do_fft(output.data(), input.data());
      else if (Quality::Medium == spectrum->quality)
         transformMedium->do_fft(output.data(), input.data());
      else if (Quality::High == spectrum->quality)
         transformHigh->do_fft(output.data(), input.data());
      else if (Quality::Ultra == spectrum->quality)
         transformUltra->do_fft(output.data(), input.data());
   }

private:
   using TransformLow = ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Low)>;
   using TransformMedium = ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Medium)>;
   using TransformHigh = ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::High)>;
   using TransformUltra = ffft::FFTRealFixLen<static_cast<uint8_t>(Quality::Ultra)>;

private:
   Spectrum* spectrum;

   TransformLow* transformLow = nullptr;
   TransformMedium* transformMedium = nullptr;
   TransformHigh* transformHigh = nullptr;
   TransformUltra* transformUltra = nullptr;
};

// spectrum

Spectrum::Spectrum(const Quality& quality)
   : quality(quality)
   , bufferSize(compileBufferSize(quality))
   , halfBufferSize(bufferSize / 2)
   , complexAmplitude(bufferSize, 0.0)
   , internal(nullptr)
{
   internal = new Internal(this);
}

Spectrum::~Spectrum()
{
   delete internal;
   internal = nullptr;
}

const Spectrum::Quality& Spectrum::getQuality() const
{
   return quality;
}

Spectrum::Map Spectrum::analyse(const Data& data, const float& sampleRate)
{
   if (bufferSize != data.size())
      return Map();

   internal->fo_fft(data, complexAmplitude);

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
