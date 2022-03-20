#ifndef BoolFieldH
#define BoolFieldH

#include <Global.h>

template <typename IntegerType>
class BoolField
{
public:
   BoolField();
   BoolField(const IntegerType& value);

public:
   BoolField& operator=(const IntegerType& value);
   operator IntegerType() const;

   size_t size() const; // the number of bits
   bool get(const uint8_t& index) const;
   void set(const uint8_t& index, const bool value);

private:
   IntegerType getMask(const uint8_t& index) const;

private:
   IntegerType data;
};

#include <BoolField.hpp>

#endif // BoolFieldH
