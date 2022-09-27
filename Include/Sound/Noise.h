#ifndef NoiseH
#define NoiseH

#include <Abstract/AbstractOscilator.h>

class Noise : public Abstract::Oscilator
{
public:
   inline Noise();
};

#ifndef NoiseHPP
#include "Noise.hpp"
#endif // NOT NoiseHPP

#endif // NOT NoiseH
