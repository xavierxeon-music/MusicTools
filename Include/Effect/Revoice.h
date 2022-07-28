#ifndef RevoiceH
#define RevoiceH

#include <Abstract/AbstractEffect.h>

#include <Sound/Spectrum.h>

class Revoice : public Abstract::BufferedEffect
{
public:
   inline Revoice();

protected:
   Data proccessBuffer(const Data &input) override;

private:
   Spectrum spectrum;
};

#ifndef RevoiceHPP
#include "../../Revoice.hpp"
#endif // NOT RevoiceHPP

#endif // NOT RevoiceH
