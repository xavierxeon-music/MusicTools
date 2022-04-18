#ifndef RememberH
#define RememberH

#include "RememberArray.h"
#include "RememberList.h"

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

   // value

   template <typename DataType>
   class Value
   {
   public:
      inline Value(Container* parent, const DataType& initialValue);

   public:
      Value& operator=(const DataType& other);
      operator DataType() const;
      operator DataType&();

   private:
      inline Value();

   private:
      DataType content;
   };

   template <typename DataType, uint16_t ArraySize>
   class ValueArray : public Array<DataType, ArraySize>
   {
   public:
      inline ValueArray(Container* parent);
      inline ValueArray(Container* parent, std::initializer_list<DataType> initialValues);

   private:
      using Remember::Array<DataType, ArraySize>::members;
   };

   template <typename DataType>
   class ValueList : public List<DataType>
   {
   public:
      inline ValueList(Container* parent);
      inline ValueList(Container* parent, std::initializer_list<DataType> initialValues);

   private:
      using Remember::List<DataType>::members;
   };

   // ref

   template <typename ContainerType>
   class Ref
   {
   public:
      Ref(Container* parent);

   public:
      Ref& operator=(const ContainerType& other);
      operator ContainerType*();
      ContainerType* operator->();
      const ContainerType* operator->() const;

   private:
      Ref();

   private:
      ContainerType container;
   };

   template <typename ContainerType, uint16_t ArraySize>
   class RefArray : public Array<ContainerType, ArraySize>
   {
   public:
      RefArray(Container* parent);

   private:
      using Remember::Array<ContainerType, ArraySize>::members;
   };

   template <typename ContainerType>
   class RefList : public List<ContainerType>
   {
   public:
      inline RefList(Container* parent);

   private:
      using Remember::List<ContainerType>::members;
   };

} // namespace Remember

#ifndef RememberHPP
#include "Remember.hpp"
#endif // NOT RememberHPP

#endif // NOT RememberH
