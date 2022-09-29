#ifndef MemoryBlockH
#define MemoryBlockH

#include <cinttypes>

#include "MemoryManager.h"

namespace Memory
{
   template <typename DataType, uint64_t BlockCount>
   class Block
   {
   protected:
      Block();
      virtual ~Block();

   protected:
      DataType* memory;

   private:
      uint64_t offset;

      static AllocMap usedBlocks;
      static AllocMap freeBlocks;
   };
} // namespace Memory

#ifndef MemoryBlockHPP
#include "MemoryBlock.hpp"
#endif // NOT MemoryBlockHPP

#endif // NOT MemoryBlockH
