#ifndef RememberContainerH
#define RememberContainerH

#include "RememberInterface.h"

namespace Remember
{
   class Container : public Interface
   {
   public:
      inline Container();

   protected:
      inline void write(RawData& rawData) const override;
      inline void read(const RawData& rawData, size_t& cursor) override;

   private:
      friend class Base;
      // clang-format off
      template <typename ContainerType> friend class Ref;
      // clang-format on
   private:
      Interface::List members;
   };
} // namespace Remember

#include <RememberContainer.hpp>

#endif //  RememberContainerH
