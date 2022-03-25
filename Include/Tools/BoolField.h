#ifndef BoolFieldH
#define BoolFieldH

#include <Global.h>

template <typename IntegerType>
class BoolField
{
public:
   BoolField();
   BoolField(IntegerType value); // no const ref to make it work with remember value

public:
   BoolField& operator=(IntegerType value);
   operator IntegerType() const;

   size_t size() const; // the number of bits
   bool get(const uint8_t& index) const;
   void set(const uint8_t& index, const bool value);

private:
   IntegerType getMask(const uint8_t& index) const;

private:
   IntegerType data;
};

using BoolField8 = BoolField<uint8_t>;
using BoolField16 = BoolField<uint16_t>;

#ifndef BoolFieldHPP
#include "../../BoolField.hpp"
#endif // NOT BoolFieldHPP

#endif // BoolFieldH
