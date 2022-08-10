#ifndef CounterH
#define CounterH

#include <MusicTools.h>

class Counter
{
public:
   pyexport inline Counter(const uint64_t& maxValue);

public:
   pyexport inline void reset();
   pyexport inline void setMaxValue(const uint64_t& newMaxValue);
   pyexport inline uint64_t valueAndNext();
   pyexport inline const uint64_t& getCurrentValue() const;
   pyexport inline bool nextAndIsMaxValue();
   pyexport inline const uint64_t& getMaxValue() const;

private:
   uint64_t maxValue;
   uint64_t currentValue;
};

#ifndef CounterHPP
#include "../../Counter.hpp"
#endif // CounterHPP

#endif // CounterH
