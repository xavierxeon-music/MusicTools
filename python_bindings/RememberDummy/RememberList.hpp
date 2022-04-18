#ifndef RememberListHPP
#define RememberListHPP

#include "RememberList.h"

namespace Remember
{
   template <class N>
   struct is_vector
   {
      static const bool test = false;
   };

   template <class N, class A>
   struct is_vector<std::vector<N, A>>
   {
      static const bool test = true;
   };

} // namespace Remember

template <typename ContentType>
Remember::List<ContentType>::List()
   : members()
{
   static_assert(!is_vector<ContentType>::test, "DataType must not be a vector");
}

template <typename ContentType>
ContentType& Remember::List<ContentType>::operator[](const uint16_t index)
{
   return members[index];
}

template <typename ContentType>
const ContentType& Remember::List<ContentType>::operator[](const uint16_t index) const
{
   return members[index];
}

template <typename ContentType>
Remember::List<ContentType>::operator std::vector<ContentType>()
{
   return members;
}

template <typename ContentType>
Remember::List<ContentType>& Remember::List<ContentType>::operator=(const std::vector<ContentType>& other)
{
   members.clear();
   for (const ContentType& value : other)
      members.push_back(value);

   return *this;
}

template <typename ContentType>
void Remember::List<ContentType>::append(const ContentType& value)
{
   members.push_back(value);
}

template <typename ContentType>
void Remember::List<ContentType>::insert(const ContentType& value, const uint64_t atIndex)
{
   if (atIndex >= size())
      members.push_back(value);
   else
      members.insert(members.begin() + atIndex, value);
}

template <typename ContentType>
bool Remember::List<ContentType>::remove(const uint64_t atIndex)
{
   if (atIndex >= size())
      return false;

   members.erase(members.begin() + atIndex);
   return true;
}

template <typename ContentType>
uint64_t Remember::List<ContentType>::size() const
{
   return members.size();
}

template <typename ContentType>
void Remember::List<ContentType>::clear()
{
   members.clear();
}

#endif // RememberListHPP
