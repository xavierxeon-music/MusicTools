#ifndef MemoryArrayH
#define MemoryArrayH

#include <initializer_list>

#include "MemoryBlock.h"

namespace Memory
{
   template <typename DataType, std::size_t ArraySize>
   class Array : public Block<DataType, ArraySize>
   {
   public:
      Array();
      Array(std::initializer_list<DataType> initialValues);

   public:
      DataType& operator[](const uint16_t index);
      const DataType& operator[](const uint16_t index) const;
      std::size_t getSize() const;
   };
} // namespace Memory

#ifndef MemoryArrayHPP
#include "MemoryArray.hpp"
#endif // NOT MemoryArrayHPP

#endif // NOT MemoryArrayH
