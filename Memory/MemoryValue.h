#ifndef MemoryValueH
#define MemoryValueH

#include "MemoryBlock.h"

namespace Memory
{
   template <typename DataType>
   class Value : public Block<DataType, 1>
   {
   public:
      Value();
      Value(const DataType& initialValue);

   public:
      Value& operator=(const DataType& value);
      operator DataType() const;
   };
} // namespace Memory

#ifndef MemoryValueHPP
#include "MemoryValue.hpp"
#endif // NOT MemoryValueHPP

#endif // NOT MemoryValueH
