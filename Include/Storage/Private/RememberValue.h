#ifndef RememberValueH
#define RememberValueH

#include "RememberBase.h"

namespace Remember
{
   // can be streamed directly

   template <typename DataType>
   class Value : public Base
   {
   public:
      Value(Container* parent, const DataType& initialValue);

   public:
      Value& operator=(const DataType& other);
      operator DataType() const;
      DataType& refValue();
      const DataType& constValue() const;

   protected:
      void write(RawData& rawData) const override;
      void read(const RawData& rawData, size_t& cursor) override;

   private:
      // clang-format off
      template <typename DataType2, uint16_t ArraySize> friend class ValueArray;
      // clang-format on

   private:
      Value();

   private:
      DataType content;
   };
} // namespace Remember

#include "RememberValue.hpp"

#endif //  RememberValueH
