#include "MemoryManager.h"

#include <cstring>

#ifdef NON_DAISY_DEVICE
#define DSY_SDRAM_BSS
#else
#include <dev/sdram.h>
#endif //  NON_DAISY_DEVICE

static constexpr std::size_t blockCount = 64 * 1024 * 1024; // 64 MB
static uint8_t DSY_SDRAM_BSS theMemory[blockCount];

Memory::Manager* Memory::Manager::me = new Memory::Manager();

Memory::Alloc Memory::Manager::alloc(std::size_t size)
{
   Alloc alloc(me->used, &theMemory[me->used]);
   me->used += size;

   return alloc;
}

Memory::Manager::Manager()
{
   std::memset(&theMemory, 0, blockCount);
}

uint64_t Memory::Manager::available()
{
   return blockCount - me->used;
}
