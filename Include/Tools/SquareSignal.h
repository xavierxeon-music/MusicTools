#ifndef SquareSignalH
#define SquareSignalH

#include <MusicTools.h>

// toggles periodically between high and low

class SquareSignal
{
public:
   inline SquareSignal(const uint8_t& halfLength, const bool& startHigh = false);

public:
   inline bool value() const;
   inline bool valueAndNext();
   inline void reset();

private:
   const uint8_t halfLength;
   const bool startHigh;
   uint8_t counter;
   bool state;
};

#ifndef SquareSignalHPP
#include "../../SquareSignal.hpp"
#endif // SquareSignalHPP

#endif // SquareSignalH
