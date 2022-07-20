#ifndef DoubleBufferH
#define DoubleBufferH

#include <MusicTools.h>

template <typename DataType, uint16_t bufferSize>
class DoubleBuffer
{
public:
   inline DoubleBuffer();

public:
   inline bool write(const DataType& data);

private:
   DataType values[2][bufferSize];
   uint16_t writeIndex;
   uint8_t bufferIndex;
};

#ifndef DoubleBufferHPP
#include "../../DoubleBuffer.hpp"
#endif // NOT DoubleBufferHPP

#endif // NOT DoubleBufferH
