#ifndef SpectrumH
#define SpectrumH

#include <map>

#include <MusicTools.h>

class Spectrum
{
public:
   using Map = std::map<float, float>; // frequency vc amplitude
public:
   Spectrum();
   ~Spectrum();

public:
   Map analyse(const Data& data, const float& sampleRate);
   static uint16_t compileBufferSize();

private:
   struct Internal;

private:
   static constexpr uint8_t frameSize = 12;
   Internal* internal;
};

#endif // NOT SpectrumH
