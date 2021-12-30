#ifndef RememberRefHPP
#define RememberRefHPP

#include <Storage/Private/RememberRef.h>

#include <type_traits>

#include <Storage/Private/RememberContainer.h>

template <typename ContainerType>
Remember::Ref<ContainerType>::Ref(Container* parent)
   : Base(parent)
   , container()
{
   static_assert(std::is_base_of<Container, ContainerType>::value, "ContainerType must inherit from container");
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
ContainerType* Remember::Ref<ContainerType>::pointer()
{
   return &container;
}

template <typename ContainerType>
const ContainerType* Remember::Ref<ContainerType>::constPointer() const
{
   return &container;
}

template <typename ContainerType>
void Remember::Ref<ContainerType>::write(RawData& rawData) const
{
   container.write(rawData);
}

template <typename ContainerType>
void Remember::Ref<ContainerType>::read(const RawData& rawData, size_t& cursor)
{
   container.read(rawData, cursor);
}

template <typename ContainerType>
Remember::Ref<ContainerType>::Ref()
   : Ref<ContainerType>(nullptr)
{
}

#endif // RememberRefHPP
