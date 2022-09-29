#ifndef MemoryManagerH
#define MemoryManagerH

#include <cinttypes>
#include <map>

namespace Memory
{
   using Alloc = std::pair<uint64_t, uint8_t*>;
   using AllocMap = std::map<uint64_t, uint8_t*>;

   class Manager
   {
   public:
      static Alloc alloc(std::size_t size);

   private:
      Manager();

   private:
      uint64_t used;
   };
} // namespace Memory

#endif // NOT MemoryManagerH
