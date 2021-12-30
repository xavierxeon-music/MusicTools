#ifndef RememberBaseHPP
#define RememberBaseHPP

#include <Storage/Private/RememberBase.h>

#include <Storage/Private/RememberContainer.h>

Remember::Base::Base(Container* parent)
   : Interface()
{
   if (parent)
   {
      parent->members.push_back(this);
   }
}

#endif // RememberBaseHPP
