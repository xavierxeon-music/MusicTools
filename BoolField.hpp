#ifndef BoolFieldHPP
#define BoolFieldHPP

#include <Tools/BoolField.h>

#include <Tools/Range.h>

template <typename IntegerType>
BoolField<IntegerType>::BoolField()
   : data{0}
{
   static_assert(std::is_integral<IntegerType>::value, "type must be an integer");
}

template <typename IntegerType>
BoolField<IntegerType>::BoolField(const IntegerType& value)
   : BoolField()
{
   *this = value;
}

template <typename IntegerType>
BoolField<IntegerType>& BoolField<IntegerType>::operator=(const IntegerType& value)
{
   data = value;
   return *this;
}

template <typename IntegerType>
BoolField<IntegerType>::operator IntegerType() const
{
   return data;
}

template <typename IntegerType>
size_t BoolField<IntegerType>::size() const
{
   return 8 * sizeof(IntegerType);
}

template <typename IntegerType>
bool BoolField<IntegerType>::get(const uint8_t& index) const
{
   const IntegerType mask = getMask();
   const IntegerType test = mask & data;

   const bool active = (test == mask);
   return active;
}

template <typename IntegerType>
void BoolField<IntegerType>::set(const uint8_t& index, const bool value)
{
   const IntegerType mask = getMask();
   if (value)
      data = mask | data;
   else
      data = ~mask & data;
}

template <typename IntegerType>
IntegerType BoolField<IntegerType>::getMask(const uint8_t& index) const
{
   const IntegerType mask = 0x01 << Range::clamp<uint8_t>(index, 0, size());
   return mask;
}

#endif // BoolFieldHPP
