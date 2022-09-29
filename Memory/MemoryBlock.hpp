#ifndef MemoryBlockHPP
#define MemoryBlockHPP

#include "MemoryBlock.h"

template <typename DataType, uint64_t BlockCount>
Memory::AllocMap Memory::Block<DataType, BlockCount>::usedBlocks = Memory::AllocMap();

template <typename DataType, uint64_t BlockCount>
Memory::AllocMap Memory::Block<DataType, BlockCount>::freeBlocks = Memory::AllocMap();

template <typename DataType, uint64_t BlockCount>
Memory::Block<DataType, BlockCount>::Block()
   : memory(nullptr)
   , offset(0)
{
   Alloc alloc = [&]()
   {
      if (freeBlocks.empty())
         return Manager::alloc(BlockCount * sizeof(DataType));

      AllocMap::iterator it = freeBlocks.begin();
      Alloc alloc = *it;
      freeBlocks.erase(it);

      return alloc;
   }();

   memory = reinterpret_cast<DataType*>(alloc.second);
   offset = alloc.first;

   usedBlocks.insert(alloc);
}

template <typename DataType, uint64_t BlockCount>
Memory::Block<DataType, BlockCount>::~Block()
{
   AllocMap::iterator it = usedBlocks.find(offset);
   if (it != usedBlocks.end())
   {
      Alloc alloc = *it;
      usedBlocks.erase(it);
      freeBlocks.insert(alloc);
   }
}

#endif // NOT MemoryBlockHPP
