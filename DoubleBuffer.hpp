#ifndef DoubleBufferHPP
#define DoubleBufferHPP

#include <Tools/DoubleBuffer.h>

template <typename DataType, uint16_t bufferSize>
DoubleBuffer<DataType, bufferSize>::DoubleBuffer()
   : values{}
   , writeIndex(0)
   , bufferIndex(0)
{
}

#endif // NOT DoubleBufferHPP
