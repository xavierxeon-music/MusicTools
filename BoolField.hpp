#ifndef BoolFieldHPP
#define BoolFieldHPP

#include <Tools/BoolField.h>

template <typename StorageType>
BoolField<StorageType>::BoolField()
   : data{0} // wiil alose set bits!
{
}

template <typename StorageType>
BoolField<StorageType>::BoolField(const StorageType& value)
   : BoolField()
{
   *this = value;
}

template <typename StorageType>
BoolField<StorageType>& BoolField<StorageType>::operator=(const StorageType& value)
{
   data = value;
   return *this;
}

template <typename StorageType>
bool& BoolField<StorageType>::operator[](const uint8_t& index)
{
   return bits[index];
}

template <typename StorageType>
const bool& BoolField<StorageType>::operator[](const uint8_t& index) const
{
   return bits[index];
}

template <typename StorageType>
BoolField<StorageType>::operator StorageType() const
{
   return data;
}

#endif // BoolFieldHPP
