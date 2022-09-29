#ifndef MemoryArrayHPP
#define MemoryArrayHPP

#include "MemoryArray.h"

template <typename DataType, std::size_t ArraySize>
Memory::Array<DataType, ArraySize>::Array()
   : Block<DataType, ArraySize>()
{
   for (uint16_t index = 0; index < ArraySize; index++)
      Block<DataType, ArraySize>::memory[index] = DataType();
}

template <typename DataType, std::size_t ArraySize>
Memory::Array<DataType, ArraySize>::Array(std::initializer_list<DataType> initialValues)
   : Block<DataType, ArraySize>()
{
   for (uint16_t index = 0; index < ArraySize; index++)
   {
      if (index < initialValues.size())
         Block<DataType, ArraySize>::memory[index] = initialValues[index];
      else
         Block<DataType, ArraySize>::memory[index] = DataType();
   }
}

template <typename DataType, std::size_t ArraySize>
DataType& Memory::Array<DataType, ArraySize>::operator[](const uint16_t index)
{
   return Block<DataType, ArraySize>::memory[index];
}

template <typename DataType, std::size_t ArraySize>
const DataType& Memory::Array<DataType, ArraySize>::operator[](const uint16_t index) const
{
   return Block<DataType, ArraySize>::memory[index];
}

template <typename DataType, std::size_t ArraySize>
std::size_t Memory::Array<DataType, ArraySize>::getSize() const
{
   return ArraySize;
}

#endif // NOT MemoryArrayHPP
