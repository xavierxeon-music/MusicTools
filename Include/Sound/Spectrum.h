#ifndef SpectrumH
#define SpectrumH

#include <MusicTools.h>

#include <ffft/FFTRealFixLen.h>

class Spectrum
{
public:
   inline Spectrum();

public:
   inline bool fill(const float& value); // return true if buffer full
   inline Data analyse();

   inline static uint16_t compileBufferSize();

private:
   static constexpr uint8_t frameSize = 12;
   const uint16_t bufferSize;
   ffft::FFTRealFixLen<frameSize> transform;

   Data buffer[2];
   uint16_t writeIndex;
   uint8_t bufferReadIndex;
   uint8_t bufferWriteIndex;
};

#ifndef SpectrumHPP
#include "../../Spectrum.hpp"
#endif // NOT SpectrumHPP

#endif // NOT SpectrumH
