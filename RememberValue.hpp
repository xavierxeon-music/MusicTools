#ifndef RememberValueHPP
#define RememberValueHPP

#include <Storage/Private/RememberValue.h>

#include <type_traits>

#include <Storage/Private/RememberContainer.h>

template <typename DataType>
Remember::Value<DataType>::Value(Container* parent, const DataType& initialValue)
   : Base(parent)
   , content(initialValue)
{
   static_assert(!std::is_base_of<Container, DataType>::value, "DataType must not inherit from container");
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
DataType& Remember::Value<DataType>::refValue()
{
   return content;
}

template <typename DataType>
const DataType& Remember::Value<DataType>::constValue() const
{
   return content;
}

template <typename DataType>
void Remember::Value<DataType>::write(RawData& rawData) const
{
   rawData.append(content);
}

template <typename DataType>
void Remember::Value<DataType>::read(const RawData& rawData, size_t& cursor)
{
   rawData.copyToValue(content, cursor);
}

template <typename DataType>
Remember::Value<DataType>::Value()
   : Value<DataType>(nullptr, 0)
{
}

#endif // RememberValueHPP
