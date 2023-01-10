#include <Abstract/AbstractChain.h>

// link

// chain

Abstract::Chain::Chain()
   : tempo()
   , linkList()
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
   (void)link;
}

void Abstract::Chain::clockTick()
{
}

void Abstract::Chain::clockReset()
{
}

// crawler

Abstract::Chain::Crawler::Crawler()
   : chainList()
{
}

Abstract::Chain::Crawler::~Crawler()
{
   for (Chain* chain : chainList)
      delete chain;

   chainList.clear();
}

void Abstract::Chain::Crawler::clockTick()
{
   for (Chain* chain : chainList)
      chain->clockTick();
}

void Abstract::Chain::Crawler::clockReset()
{
   for (Chain* chain : chainList)
      chain->clockReset();
}

void Abstract::Chain::Crawler::addChain(Chain* chain)
{
   chainList.push_back(chain);
}
