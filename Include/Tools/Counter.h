#ifndef CounterH
#define CounterH

#include <MusicTools.h>

class Counter
{
public:
   inline Counter(const uint64_t& maxValue);

public:
   inline void reset();
   inline void setMaxValue(const uint64_t& newMaxValue);
   inline uint64_t valueAndNext();
   inline const uint64_t& getCurrentValue() const;
   inline bool nextAndIsMaxValue();
   inline const uint64_t& getMaxValue() const;

private:
   uint64_t maxValue;
   uint64_t currentValue;
};

#ifndef CounterHPP
#include "../../Counter.hpp"
#endif // CounterHPP

#endif // CounterH
