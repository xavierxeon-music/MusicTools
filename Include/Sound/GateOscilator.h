#ifndef GateOscilatorH
#define GateOscilatorH

#include <Abstract/AbstractOscilator.h>

#include <Utility/SquareSignal.h>

// a sqaure oscilator at the highest possible pitch

// use slew limiter to turn into proper gate, eg:
// * Mutalbe Instruments Stages (1 green stage, slider down)
// * Jouranalouge Contour 1

class GateOscilator : public Abstract::Oscilator
{
public:
   inline GateOscilator();

public:
   inline float createSound() override;
   inline void setOn(bool on);

private:
   bool isOn;
   SquareSignal square;
};

#ifndef GateOscilatorHPP
#include "../../GateOscilator.hpp"
#endif // NOT GateOscilatorHPP

#endif // NOT GateOscilator
