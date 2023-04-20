#ifndef AbstractSegmentCrawlerH
#define AbstractSegmentCrawlerH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

namespace Abstract
{
   // has  fixed length of segments and therefore a fixed length

   class SegmentCrawler
   {
   public:
      SegmentCrawler();

   public:
      virtual void clear();
      virtual void update(const Tempo::Tick& newDefaultLength, const uint32_t newSegmentCount);

      void clockTick();
      void clockReset();

      const Tempo::Tick& getDefaultLength() const;
      const uint32_t& getSegmentCount() const;

      const std::string& getSegmentName(const uint32_t index) const;
      void setSegmentName(const uint32_t index, const std::string& name);

      Tempo::Tick getSegmentLength(const uint32_t index, bool* isDefault = nullptr) const;
      virtual void setSegmentLength(const uint32_t index, const Tempo::Tick& length);

      bool isLooping() const;
      bool isPastLoop() const;
      void setLooping(bool on);

      const uint32_t& getCurrentSegmentIndex() const;
      uint8_t getCurrentSegmentTick() const;
      void setCurrentSegmentIndex(const uint32_t index);
      float getCurrentSegmentPrecentage(const float tickPercentage) const;

      virtual void updateProxies();

   private:
      class Header
      {
      public:
         Header();
         Header(const Header& other);
         Header& operator=(const Header& other);

      public:
         std::string name;
         uint8_t length;
      };

   private:
      QList<Header> headers;
      Tempo::Tick defaultLength;
      uint32_t segmentCount;
      bool loop;

      uint32_t currentSegmentIndex;
      Counter divisionCounter;
      bool pastLoop;
      bool firstTickDone;
   };
} // namespace Abstract

#endif // NOT AbstractSegmentCrawlerH
