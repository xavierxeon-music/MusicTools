#ifndef RandomChainH
#define RandomChainH

#include <Abstract/AbstractChainCrawler.h>

class RandomChain : public Abstract::Chain
{
public:
   class Link : public Abstract::Chain::Link
   {
   private:
      uint8_t startValue;
      uint8_t endValue;
   };

public:
   inline RandomChain();
};

#ifndef RandomChainHPP
#include "../../RandomChain.hpp"
#endif // NOT RandomChainHPP

#endif // NOT RandomChainH
