#ifndef RememberH
#define RememberH

// this is a dummy implementation

namespace Remember
{
   struct Root
   {
      inline static void setUnsynced();
   };

   struct Container
   {
   };

   template <typename DataType>
   class Value
   {
   public:
      inline Value(Container* parent, const DataType& initialValue);

   public:
      inline Value& operator=(const DataType& other);
      inline operator DataType() const;
      inline DataType& refValue();
      const DataType& constValue() const;

   private:
      // clang-format off
      template <typename DataType2, uint16_t ArraySize> friend class ValueArray;
      // clang-format on

   private:
      inline Value();

   private:
      DataType content;
   };

   template <typename DataType, uint16_t ArraySize>
   class ValueArray
   {
   public:
      inline ValueArray(Container* parent);
      inline ValueArray(Container* parent, std::initializer_list<DataType> initialValues);

   public:
      Value<DataType>& operator[](const uint16_t index);
      inline const Value<DataType>& operator[](const uint16_t index) const;

   private:
      Value<DataType> members[ArraySize];
   };

} // namespace Remember

#include "Remember.hpp"

#endif // RememberH
