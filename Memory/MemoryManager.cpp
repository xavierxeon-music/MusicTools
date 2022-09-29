#include "MemoryManager.h"

#include <cstring>

#include <MusicTools.h>

static constexpr uint64_t blockCount = 64 * 1024 * 1024;
static uint8_t DSY_SDRAM_BSS theMemory[blockCount];

Memory::Alloc Memory::Manager::alloc(std::size_t size)
{
   static Manager* me = new Manager();

   Alloc alloc(me->used, &theMemory[me->used]);
   me->used += size;

   return alloc;
}

Memory::Manager::Manager()
{
   std::memset(&theMemory, 0, blockCount);
}
