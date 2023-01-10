#ifndef AbstractChainCrawlerH
#define AbstractChainCrawlerH

#include <Remember.h>

#include <Music/Tempo.h>

namespace Abstract
{
   // a collection of chains. each link can have an arbitrary length.

   class Chain
   {
   public:
      using List = std::list<Chain*>;

      class Link
      {
      public:
         using List = std::vector<Link*>;

      protected:
         Tempo::Tick length;
      };

      class Crawler final
      {
      public:
         Crawler();
         ~Crawler();

      public:
         void clockTick();
         void clockReset();

         void addChain(Chain* chain);

      private:
         Chain::List chainList;
      };

   public:
      Chain();
      ~Chain();

   public:
      void addLink(Link* link);
      virtual void linkDone(Link* link);

   private:
      void clockTick();
      void clockReset();

   private:
      TempoControl tempo;
      Link::List linkList;
   };
} // namespace Abstract

#endif // NOT AbstractChainCrawlerH
