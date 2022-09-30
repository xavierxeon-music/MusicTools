#ifndef MemoryManagerH
#define MemoryManagerH

#include <cinttypes>
#include <map>

// Allocate a block of 64 MB of memory.
// On a daisy device this will the the SDRAM

namespace Memory
{
   using Alloc = std::pair<uint64_t, uint8_t*>;
   using AllocMap = std::map<uint64_t, uint8_t*>;

   class Manager
   {
   public:
      static Alloc alloc(std::size_t size);
      static uint64_t available();

   private:
      Manager();

   private:
      static Manager* me;
      std::size_t used;
   };
} // namespace Memory

#endif // NOT MemoryManagerH
