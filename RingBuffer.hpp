#ifndef RingBufferHPP
#define RingBufferHPP

#include <Tools/RingBuffer.h>

template <uint8_t bufferSize>
RingBuffer<bufferSize>::RingBuffer()
   : values()
   , currentIndex(0)
   , filled(false)
{
}

template <uint8_t bufferSize>
RingBuffer<bufferSize>& RingBuffer<bufferSize>::operator+=(uint8_t value)
{
   add(value);
   return *this;
}

template <uint8_t bufferSize>
RingBuffer<bufferSize>::operator uint8_t() const
{
   return average();
}

template <uint8_t bufferSize>
void RingBuffer<bufferSize>::add(uint8_t value)
{
   values[currentIndex] = value;
   currentIndex++;

   if (bufferSize <= currentIndex)
   {
      currentIndex = 0;
      if (!filled)
         filled = true;
   }
}

template <uint8_t bufferSize>
void RingBuffer<bufferSize>::clear()
{
   currentIndex = 0;
   filled = false;
}

template <uint8_t bufferSize>
uint8_t RingBuffer<bufferSize>::average() const
{
   if (!filled && 0 == currentIndex)
      return 0;

   float sum = 0;

   uint8_t maxIndex = filled ? bufferSize : currentIndex;
   for (uint8_t index = 0; index < bufferSize; index++)
      sum += values[index];

   const float fAverage = sum / static_cast<float>(maxIndex);
   return static_cast<uint8_t>(fAverage);
}

#endif // RingBufferHPP
