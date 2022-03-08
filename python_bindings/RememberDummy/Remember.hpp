#ifndef RememberHPP
#define RememberHPP

#include "Remember.h"

// root
void Remember::Root::setUnsynced()
{
}

// value

template <typename DataType>
Remember::Value<DataType>::Value(Container* parent, const DataType& initialValue)
   : content(initialValue)
{
   (void)parent;
}

template <typename DataType>
Remember::Value<DataType>& Remember::Value<DataType>::operator=(const DataType& other)
{
   content = other;
   return *this;
}

template <typename DataType>
Remember::Value<DataType>::operator DataType() const
{
   return content;
}

template <typename DataType>
DataType& Remember::Value<DataType>::refValue()
{
   return content;
}

template <typename DataType>
const DataType& Remember::Value<DataType>::constValue() const
{
   return content;
}

template <typename DataType>
Remember::Value<DataType>::Value()
   : content(DataType(0))
{
}

// value array

template <typename DataType, uint16_t ArraySize>
Remember::ValueArray<DataType, ArraySize>::ValueArray(Container* parent)
   : members()
{
   (void)parent;
}

template <typename DataType, uint16_t ArraySize>
Remember::ValueArray<DataType, ArraySize>::ValueArray(Container* parent, std::initializer_list<DataType> initialValues)
   : ValueArray<DataType, ArraySize>(parent)
{
   uint16_t index = 0;
   for (const DataType& value : initialValues)
   {
      members[index].refValue() = value;
      index++;
      if (index == ArraySize)
         break;
   }
}

template <typename DataType, uint16_t ArraySize>
Remember::Value<DataType>& Remember::ValueArray<DataType, ArraySize>::operator[](const uint16_t index)
{
   return members[index];
}

template <typename DataType, uint16_t ArraySize>
const Remember::Value<DataType>& Remember::ValueArray<DataType, ArraySize>::operator[](const uint16_t index) const
{
   return members[index];
}

#endif // RememberHPP
