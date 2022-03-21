#ifndef RingBufferHPP
#define RingBufferHPP

#include <Tools/RingBuffer.h>

template <typename DataType, uint8_t bufferSize>
RingBuffer<DataType, bufferSize>::RingBuffer()
   : values()
   , currentIndex(0)
   , filled(false)
{
   static_assert(std::is_arithmetic<DataType>::value, "type must be an numeric type");
}

template <typename DataType, uint8_t bufferSize>
RingBuffer<DataType, bufferSize>& RingBuffer<DataType, bufferSize>::operator+=(DataType value)
{
   add(value);
   return *this;
}

template <typename DataType, uint8_t bufferSize>
RingBuffer<DataType, bufferSize>::operator DataType() const
{
   return average();
}

template <typename DataType, uint8_t bufferSize>
void RingBuffer<DataType, bufferSize>::add(DataType value)
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

template <typename DataType, uint8_t bufferSize>
void RingBuffer<DataType, bufferSize>::clear()
{
   currentIndex = 0;
   filled = false;
}

template <typename DataType, uint8_t bufferSize>
DataType RingBuffer<DataType, bufferSize>::average() const
{
   if (!filled && 0 == currentIndex)
      return 0;

   float sum = 0;

   uint8_t maxIndex = filled ? bufferSize : currentIndex;
   for (uint8_t index = 0; index < bufferSize; index++)
      sum += values[index];

   const float fAverage = sum / static_cast<float>(maxIndex);
   return static_cast<DataType>(fAverage);
}

#endif // RingBufferHPP
