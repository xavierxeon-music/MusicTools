#ifndef RevoiceH
#define RevoiceH

#include <Abstract/AbstractEffect.h>

#include <Sound/Spectrum.h>
#include <Sound/StandardTable.h>
#include <Sound/WaveTable.h>
#include <Sound/WaveTableOscilator.h>

pyexport class Revoice : public Abstract::ThreadeBufferEffect
{
public:
   pyexport inline Revoice(const uint8_t& numberOfVocices = 16, const Spectrum::Quality& quality = Spectrum::Quality::Low);
   inline ~Revoice();

public:
   pyexport inline const uint8_t& getNumberOfVoices() const;
   pyexport inline void setNumberOfVoices(const uint8_t& newNumberOfVocices);
   pyexport inline void setSampleRate(const float& newSampleRate);
   pyexport inline Data convert(const Data& input);

protected:
   inline Data proccessBuffer(const Data& input) override;

private:
   using AmplitudeMap = std::map<float, float>;

private:
   uint8_t numberOfVocices;
   WaveTable::Oscilator* oscilators;
   Standard::Table sineTable;

   float sampleRate;
   Spectrum spectrum;
};

#ifndef RevoiceHPP
#include "../../Revoice.hpp"
#endif // NOT RevoiceHPP

#endif // NOT RevoiceH
