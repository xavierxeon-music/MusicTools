#ifndef RememberBaseH
#define RememberBaseH

#include "RememberInterface.h"

namespace Remember
{
   class Container;


   class Base : public Interface
   {
   public:
      inline Base(Container* parent);
   };
} // namespace Remember

#include <RememberBase.hpp>

#endif //  RememberBaseH
