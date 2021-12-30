#ifndef RememberRefArrayHPP
#define RememberRefArrayHPP

#include <Storage/Private/RememberRefArray.h>

#include <type_traits>

#include <Storage/Private/RememberContainer.h>

template <typename ContainerType, uint16_t ArraySize>
Remember::RefArray<ContainerType, ArraySize>::RefArray(Container* parent)
   : Base(parent)
   , members()
{
   static_assert(std::is_base_of<Container, ContainerType>::value, "ContainerType must inherit from container");
}

template <typename ContainerType, uint16_t ArraySize>
Remember::Ref<ContainerType>& Remember::RefArray<ContainerType, ArraySize>::operator[](const uint16_t index)
{
   return members[index];
}

template <typename ContainerType, uint16_t ArraySize>
const Remember::Ref<ContainerType>& Remember::RefArray<ContainerType, ArraySize>::operator[](const uint16_t index) const
{
   return members[index];
}

template <typename ContainerType, uint16_t ArraySize>
void Remember::RefArray<ContainerType, ArraySize>::write(RawData& rawData) const
{
   for (uint16_t index = 0; index < ArraySize; index++)
      members[index].write(rawData);
}

template <typename ContainerType, uint16_t ArraySize>
void Remember::RefArray<ContainerType, ArraySize>::read(const RawData& rawData, size_t& cursor)
{
   for (uint16_t index = 0; index < ArraySize; index++)
      members[index].read(rawData, cursor);
}

#endif // RememberRefArrayHPP
