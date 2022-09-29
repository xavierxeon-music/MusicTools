#ifndef MemoryValueHPP
#define MemoryValueHPP

#include "MemoryValue.h"

template <typename DataType>
Memory::Value<DataType>::Value()
   : Block<DataType, 1>()
{
   Block<DataType, 1>::memory[0] = DataType();
}

template <typename DataType>
Memory::Value<DataType>::Value(const DataType& initialValue)
   : Block<DataType, 1>()
{
   Block<DataType, 1>::memory[0] = initialValue;
}

template <typename DataType>
Memory::Value<DataType>& Memory::Value<DataType>::operator=(const DataType& value)
{
   Block<DataType, 1>::memory[0] = value;
   return *this;
}

template <typename DataType>
Memory::Value<DataType>::operator DataType() const
{
   return Block<DataType, 1>::memory[0];
}

#endif // NOT MemoryValueHPP
