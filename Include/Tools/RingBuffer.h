#ifndef RingBufferH
#define RingBufferH

#include <MusicTools.h>

template <typename DataType, uint8_t bufferSize>
class RingBuffer
{
public:
   RingBuffer();

public:
   RingBuffer& operator+=(DataType value); // add
   operator DataType() const;              // average

public:
   void add(DataType value);
   void clear();
   DataType average() const;

private:
   DataType values[bufferSize];
   uint8_t currentIndex;
   bool filled;
};

#ifndef ReingBufferHPP
#include "../../RingBuffer.hpp"
#endif // NOT RingBufferHPP

#endif // NOT RingBufferH
