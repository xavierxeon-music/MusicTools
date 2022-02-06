#ifndef BoolFieldH
#define BoolFieldH

#include <Global.h>

template <typename StorageType>
class BoolField
{
public:
   BoolField();
   BoolField(const StorageType& value);

public:
   BoolField& operator=(const StorageType& value);
   bool& operator[](const uint8_t& index);
   const bool& operator[](const uint8_t& index) const;
   operator StorageType() const;

private:
   union
   {
      StorageType data;
      bool bits[sizeof(StorageType)];
   };
};

#include <BoolField.hpp>

#endif // BoolFieldH
