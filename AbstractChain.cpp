#include <Abstract/AbstractChain.h>

// link

Abstract::Chain::Link::Link()
   : length(1)
   , tickCounter(length)
{
}

Abstract::Chain::Link::~Link()
{
}

void Abstract::Chain::Link::setLength(const Tempo::Tick& newLength)
{
   length = newLength;
   tickCounter.setMaxValue(newLength);
   tickCounter.reset();
}

// chain

Abstract::Chain::Chain()
   : linkList()
{
}

Abstract::Chain::~Chain()
{
   for (Link* link : linkList)
      delete link;
   linkList.clear();
}

void Abstract::Chain::addLink(Link* link)
{
   linkList.push_back(link);
}

void Abstract::Chain::linkDone(Link* link)
{
   delete link;
}

void Abstract::Chain::clockTick()
{
   if (linkList.empty())
      return;

   Link* current = linkList.front();
   if (current->tickCounter.nextAndIsMaxValue())
   {
      linkList.pop_front();
      linkDone(current);
   }
}

void Abstract::Chain::clockReset()
{
   if (linkList.empty())
      return;

   Link* current = linkList.front();
   current->tickCounter.reset();
}

float Abstract::Chain::getCurrentLinkPrecentage(const float tickPercentage) const
{
   if (linkList.empty())
      return 0.0;

   const Link* current = linkList.front();

   float currentTick = current->tickCounter.getCurrentValue();
   const float maxTick = current->tickCounter.getMaxValue();

   if (currentTick != maxTick && 0.0 < tickPercentage && 1.0 > tickPercentage)
      currentTick += tickPercentage;

   const float percentage = currentTick / maxTick;

   return percentage;
}

// Collection

Abstract::Chain::Collection::Collection()
   : chainList()
{
}

Abstract::Chain::Collection::~Collection()
{
   chainList.clear();
}

void Abstract::Chain::Collection::addChain(Chain* chain)
{
   chainList.push_back(chain);
}

void Abstract::Chain::Collection::clockTick()
{
   for (Chain* chain : chainList)
      chain->clockTick();
}

void Abstract::Chain::Collection::clockReset()
{
   for (Chain* chain : chainList)
      chain->clockReset();
}
