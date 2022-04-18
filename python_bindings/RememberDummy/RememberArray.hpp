#ifndef RememberArrayHPP
#define RememberArrayHPP

#include "RememberArray.h"

template <typename ContentType, uint16_t ArraySize>
Remember::Array<ContentType, ArraySize>::Array()
   : members()
{
}

template <typename ContentType, uint16_t ArraySize>
ContentType& Remember::Array<ContentType, ArraySize>::operator[](const uint16_t index)
{
   return members[index];
}

template <typename ContentType, uint16_t ArraySize>
const ContentType& Remember::Array<ContentType, ArraySize>::operator[](const uint16_t index) const
{
   return members[index];
}

template <typename ContentType, uint16_t ArraySize>
uint16_t Remember::Array<ContentType, ArraySize>::getSize() const
{
   return ArraySize;
}

#endif // RememberArrayHPP
