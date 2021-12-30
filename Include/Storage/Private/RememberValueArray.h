#ifndef RememberValueArrayH
#define RememberValueArrayH

#include "RememberBase.h"

#include <initializer_list>

#include <MusicTools.h>

#include "RememberValue.h"

namespace Remember
{
   // array of things that can stream directly

   template <typename DataType, uint16_t ArraySize>
   class ValueArray : public Base
   {
   public:
      ValueArray(Container* parent);
      ValueArray(Container* parent, std::initializer_list<DataType> initialValues);

   public:
      Value<DataType>& operator[](const uint16_t index);
      const Value<DataType>& operator[](const uint16_t index) const;

   protected:
      void write(RawData& rawData) const override;
      void read(const RawData& rawData, size_t& cursor) override;

   private:
      Value<DataType> members[ArraySize];
   };
} // namespace Remember

#include "RememberValueArray.hpp"

#endif //  RememberValueArrayH
