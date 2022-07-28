#ifndef RevoiceH
#define RevoiceH

#include <Abstract/AbstractEffect.h>

#include <Sound/Spectrum.h>
#include <Sound/StandardTable.h>
#include <Sound/WaveTable.h>

class Revoice : public Abstract::BufferedEffect
{
public:
   inline Revoice();

public:
   inline void setSampleRate(const float& newSampleRate);
   inline Data convert(const Data& input);

protected:
   inline Data proccessBuffer(const Data& input) override;

private:
   using AmplitudeMap = std::map<float, float>;

private:
   static constexpr uint8_t numberOfVocices = 16;
   WaveTable::Oscilator oscilators[numberOfVocices];
   Standard::Table sineTable;

   float sampleRate;
   Spectrum spectrum;
};

#ifndef RevoiceHPP
#include "../../Revoice.hpp"
#endif // NOT RevoiceHPP

#endif // NOT RevoiceH
