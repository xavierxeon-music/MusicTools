#ifndef RememberInterfaceH
#define RememberInterfaceH

#include <MusicTools.h>

#include "RememberRawData.h"

namespace Remember
{
   class Interface
   {
   public:
      using List = std::vector<Interface*>;

   public:
      virtual void write(RawData& rawData) const = 0;
      virtual void read(const RawData& rawData, size_t& cursor) = 0;
   };

} // namespace Remember

#endif //  RememberInterfaceH
