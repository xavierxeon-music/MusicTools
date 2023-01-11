#ifndef AbstractChainH
#define AbstractChainH

#include <Remember.h>

#include <Music/Tempo.h>

namespace Abstract
{

   class Chain
   {
   public:
      using List = std::list<Chain*>;

      class Link
      {
      public:
         using List = std::list<Link*>;

      public:
         Link();
         virtual ~Link();

      public:
         void setLength(const Tempo::Tick& newLength);

      private:
         friend class Chain;

      private:
         Tempo::Tick length;
         Counter tickCounter;
      };

      // a collection of chains. each link can have an arbitrary length.
      class Collection final
      {
      public:
         Collection();
         ~Collection();

      public:
         void addChain(Chain* chain); // does not take ownership
         void clockTick();
         void clockReset();

      private:
         Chain::List chainList;
      };

   public:
      Chain();
      virtual ~Chain();

   public:
      void clockTick();
      void clockReset();
      float getCurrentLinkPrecentage(const float& tickPercentage) const;

   protected:
      void addLink(Link* link);              // add link to list, but does not take ownership
      virtual void linkDone(Link* link) = 0; // link has been removed form list. chain will not delete link
      bool hasLinks() const;

   private:
      Link::List linkList;
   };
} // namespace Abstract

#endif // NOT AbstractChainCrawlerH
