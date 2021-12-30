#ifndef RingBufferH
#define RingBufferH

#include <Global.h>

template <uint8_t bufferSize>
class RingBuffer
{
public:
   RingBuffer();

public:
   RingBuffer& operator+=(uint8_t value); // add
   operator uint8_t() const;              // average

public:
   void add(uint8_t value);
   void clear();
   uint8_t average() const;

private:
   uint8_t values[bufferSize];
   uint8_t currentIndex;
   bool filled;
};

#include <RingBuffer.hpp>

#endif // RingBufferH
