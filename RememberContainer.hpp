#ifndef RememberContainerHPP
#define RememberContainerHPP

#include <Storage/Private/RememberContainer.h>

Remember::Container::Container()
   : Interface()
   , members()
{
}

void Remember::Container::write(RawData& rawData) const
{
   for (Interface* member : members)
      member->write(rawData);
}

void Remember::Container::read(const RawData& rawData, size_t& cursor)
{
   for (Interface* member : members)
      member->read(rawData, cursor);
}

#endif // RememberContainerHPP
