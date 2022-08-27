#ifndef RememberHPP
#define RememberHPP

#include "Remember.h"

#include <string>

// root
void Remember::Root::setUnsynced()
{
}

// value

template <typename DataType>
Remember::Value<DataType>::Value(Container* parent, const DataType& initialValue)
   : content(initialValue)
{
}

template <typename DataType>
Remember::Value<DataType>& Remember::Value<DataType>::operator=(const DataType& other)
{
   content = other;
   return *this;
}

template <typename DataType>
Remember::Value<DataType>::operator DataType() const
{
   return content;
}

template <typename DataType>
Remember::Value<DataType>::operator DataType&()
{
   return content;
}

template <typename DataType>
Remember::Value<DataType>::Value()
   : Value<DataType>(nullptr, 0)
{
}

// value array

template <typename DataType, uint16_t ArraySize>
Remember::ValueArray<DataType, ArraySize>::ValueArray(Container* parent)
   : Remember::Array<DataType, ArraySize>()
{
}

template <typename DataType, uint16_t ArraySize>
Remember::ValueArray<DataType, ArraySize>::ValueArray(Container* parent, std::initializer_list<DataType> initialValues)
   : ValueArray<DataType, ArraySize>(parent)
{
   uint16_t index = 0;
   for (const DataType& value : initialValues)
   {
      members[index] = value;
      index++;
      if (index == ArraySize)
         break;
   }
}

// value list

template <typename DataType>
Remember::ValueList<DataType>::ValueList(Container* parent)
   : Remember::List<DataType>()
{
}

template <typename DataType>
Remember::ValueList<DataType>::ValueList(Container* parent, std::initializer_list<DataType> initialValues)
   : ValueList<DataType>(parent)
{
   for (const DataType& value : initialValues)
      members.push_back(value);
}

// string

Remember::String::String(Container* parent)
   : ValueList<char>(parent)
{
}

Remember::String::String(Container* parent, const std::string& text)
   : ValueList<char>(parent)
{
   *this = text;
}

Remember::String& Remember::String::operator=(const std::string& text)
{
   members.clear();

   for (const char& letter : text)
      append(letter);

   return *this;
}

Remember::String::operator std::string() const
{
   std::string text;
   for (const char& letter : members)
      text += letter;

   return text;
}

// ref

template <typename ContainerType>
Remember::Ref<ContainerType>::Ref(Container* parent)
   : container()
{
}

template <typename ContainerType>
Remember::Ref<ContainerType>& Remember::Ref<ContainerType>::operator=(const ContainerType& other)
{
   container = other;
   return *this;
}

template <typename ContainerType>
Remember::Ref<ContainerType>::operator ContainerType*()
{
   return &container;
}

template <typename ContainerType>
ContainerType* Remember::Ref<ContainerType>::operator->()
{
   return &container;
}

template <typename ContainerType>
const ContainerType* Remember::Ref<ContainerType>::operator->() const
{
   return &container;
}
template <typename ContainerType>
Remember::Ref<ContainerType>::Ref()
   : Ref<ContainerType>(nullptr)
{
}

// ref array

template <typename ContainerType, uint16_t ArraySize>
Remember::RefArray<ContainerType, ArraySize>::RefArray(Container* parent)
   : Remember::Array<ContainerType, ArraySize>()
{
}

// ref list

template <typename ContainerType>
Remember::RefList<ContainerType>::RefList(Container* parent)
   : Remember::List<ContainerType>()
{
}

#endif // RememberHPP
