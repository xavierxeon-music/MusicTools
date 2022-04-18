#ifndef RememberListH
#define RememberListH

#include <vector>

namespace Remember
{
   template <typename ContentType>
   class List
   {
   public:
      inline List();

   public:
      inline ContentType& operator[](const uint16_t index);
      inline const ContentType& operator[](const uint16_t index) const;

      inline operator std::vector<ContentType>();
      inline List<ContentType>& operator=(const std::vector<ContentType>& other);

      inline void append(const ContentType& value);
      inline void insert(const ContentType& value, const uint64_t atIndex);
      inline bool remove(const uint64_t atIndex);
      inline void clear();

      inline uint64_t size() const;

   protected:
      std::vector<ContentType> members;
   };
} // namespace Remember

#ifndef RememberListHPP
#include "RememberList.hpp"
#endif // NOT RememberListHPP

#endif // RememberListH
