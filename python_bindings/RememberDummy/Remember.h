#ifndef RememberH
#define RememberH

// this is a dummy implementation

namespace Remember
{
   struct Root
   {
      static void setUnsynced() {}
   };

   struct Container
   {
   };

   template <typename DataType>
   class Value
   {
   public:
      Value(Container* parent, const DataType& initialValue)
         : content(initialValue)
      {
         (void)parent;
      }

   public:
      Value& operator=(const DataType& other)
      {
         content = other;
         return *this;
      }

      operator DataType() const
      {
         return content;
      }

      DataType& refValue()
      {
         return content;
      }

      const DataType& constValue() const
      {
         return content;
      }

   private:
      // clang-format off
      template <typename DataType2, uint16_t ArraySize> friend class ValueArray;
      // clang-format on

   private:
      Value();

   private:
      DataType content;
   };

   template <typename DataType, uint16_t ArraySize>
   class ValueArray
   {
   public:
      ValueArray(Container* parent)
         : members()
      {
         (void)parent;
      }

      ValueArray(Container* parent, std::initializer_list<DataType> initialValues)
         : ValueArray<DataType, ArraySize>(parent)
      {
         uint16_t index = 0;
         for (const DataType& value : initialValues)
         {
            members[index].refValue() = value;
            index++;
            if (index == ArraySize)
               break;
         }
      }

   public:
      Value<DataType>& operator[](const uint16_t index)
      {
         return members[index];
      }

      const Value<DataType>& operator[](const uint16_t index) const
      {
         return members[index];
      }

   private:
      Value<DataType> members[ArraySize];
   };

} // namespace Remember

#endif // RememberH
