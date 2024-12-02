#ifndef RingBufferH
#define RingBufferH

#include <MusicTools.h>

template <typename DataType, uint16_t bufferSize>
class RingBuffer
{
public:
   RingBuffer();

public:
   RingBuffer& operator+=(DataType value); // add
   operator DataType() const;              // average

public:
   DataType add(DataType value); // returns value overwritten
   void clear();
   DataType average() const;

private:
   DataType values[bufferSize];
   uint16_t currentIndex;
   bool filled;
};

#ifndef RingBufferHPP
#include "../../RingBuffer.hpp"
#endif // NOT RingBufferHPP

#endif // NOT RingBufferH
