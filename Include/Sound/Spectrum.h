#ifndef SpectrumH
#define SpectrumH

#include <map>

#include <MusicTools.h>

namespace ffft
{
   class FFTBase;
}

class Spectrum
{
public:
   using Map = std::map<float, float>; // frequency vc amplitude
   enum class Quality : uint8_t
   {
      Low = 10,
      Medium = 11,
      High = 12,
      Ultra = 13

   };

public:
   Spectrum(const Quality& quality = Quality::High);
   ~Spectrum();

public:
   const Quality& getQuality() const;
   Map analyse(const Data& data, const float& sampleRate);
   static uint16_t compileBufferSize(const Quality& quality = Quality::High);

private:
   void init();
   void clear();

private:
   const Quality quality;
   const uint16_t bufferSize;
   const uint16_t halfBufferSize;
   Data complexAmplitude;

   ffft::FFTBase* transform;
};

#endif // NOT SpectrumH
