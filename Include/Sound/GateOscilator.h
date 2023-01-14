#ifndef GateOscilatorH
#define GateOscilatorH

#include <Abstract/AbstractOscilator.h>

#include <Utility/SquareSignal.h>

// a sqaure oscilator at the highest possible pitch
// per default oscilates between -1 and 1

// use slew limiter or decay envelope to turn into proper gate, eg:
// * Mutalbe Instruments Stages (1 green stage, slider down)
// * Jouranalouge Contour 1

class GateOscilator : public Abstract::Oscilator
{
public:
   inline GateOscilator();

public:
   inline float createSound() override;
   inline void setOn(bool on);
   inline void setMinValue(const float& value);
   inline void setMaxValue(const float& value);

private:
   bool isOn;
   SquareSignal square;
   float minValue;
   float maxValue;
};

#ifndef GateOscilatorHPP
#include "../../GateOscilator.hpp"
#endif // NOT GateOscilatorHPP

#endif // NOT GateOscilator
