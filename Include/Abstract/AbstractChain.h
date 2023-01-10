#ifndef AbstractChainH
#define AbstractChainH

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

      private:
         friend class Chain;
      };

      class Crawler final
      {
      public:
         Crawler();
         ~Crawler();

      public:
         void clockTick();
         void clockReset();

         void addChain(Chain* chain); // does not take ownership

      private:
         Chain::List chainList;
      };

   public:
      Chain();
      virtual ~Chain();

   public:
      void addLink(Link* link);          // does not take ownership
      virtual void linkDone(Link* link); // does not delete link

   private:
      void clockTick();
      void clockReset();

   private:
      TempoControl tempo;
      Link::List linkList;
   };
} // namespace Abstract

#endif // NOT AbstractChainCrawlerH
