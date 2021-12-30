#ifndef RememberRefArrayH
#define RememberRefArrayH

#include "RememberBase.h"

#include <MusicTools.h>

#include "RememberRef.h"

namespace Remember
{
   // array of things that can be streamed via container

   template <typename ContainerType, uint16_t ArraySize>
   class RefArray : public Base
   {
   public:
      RefArray(Container* parent);

   public:
      Ref<ContainerType>& operator[](const uint16_t index);
      const Ref<ContainerType>& operator[](const uint16_t index) const;

   protected:
      void write(RawData& rawData) const override;
      void read(const RawData& rawData, size_t& cursor) override;

   private:
      Ref<ContainerType> members[ArraySize];
   };
} // namespace Remember

#include "RememberRefArray.hpp"

#endif //  RememberRefArrayH
