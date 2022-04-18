#ifndef RememberArrayH
#define RememberArrayH

#include <cinttypes>

namespace Remember
{
   template <typename ContentType, uint16_t ArraySize>
   class Array
   {
   public:
      inline Array();

   public:
      ContentType& operator[](const uint16_t index);
      const ContentType& operator[](const uint16_t index) const;
      uint16_t getSize() const;

   protected:
      ContentType members[ArraySize];
   };
} // namespace Remember

#ifndef RememberArrayHPP
#include "RememberArray.hpp"
#endif // NOT RememberArrayHPP

#endif // RememberArrayH
