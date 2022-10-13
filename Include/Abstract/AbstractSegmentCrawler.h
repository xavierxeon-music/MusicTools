#ifndef AbstractSegmentCrawlerH
#define AbstractSegmentCrawlerH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

pyexport namespace Abstract
{
   pyexport class SegmentCrawler : public Remember::Container
   {
   public:
      static const Color fgDefaultColor;
      static const Color bgDefaultColor;

   public:
      pyexport SegmentCrawler();

   public:
      pyexport virtual void clear();
      pyexport virtual void update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount);

      pyexport void clockTick();
      pyexport void clockReset();

      pyexport const uint8_t& getDefaultDivision() const;
      pyexport const uint32_t& getSegmentCount() const;

      pyexport const std::string& getSegmentName(const uint32_t index) const;
      pyexport void setSegmentName(const uint32_t index, const std::string& name);

      pyexport uint8_t getSegmentLength(const uint32_t index, bool* isDefault = nullptr) const;
      pyexport virtual void setSegmentLength(const uint32_t index, const uint8_t& length);

      pyexport Color getSegmentForegroundColor(const uint32_t index, bool* isDefault = nullptr) const;
      pyexport void setSegmentForegroundColor(const uint32_t index, const Color& color = fgDefaultColor);

      pyexport Color getSegmentBackgroundColor(const uint32_t index, bool* isDefault = nullptr) const;
      pyexport void setSegmentBackgroundColor(const uint32_t index, const Color& color = bgDefaultColor);

      pyexport bool isLooping() const;
      pyexport void setLooping(bool on);

      pyexport const uint32_t& getCurrentSegmentIndex() const;
      pyexport uint8_t getCurrentSegmentTick() const;
      pyexport void setCurrentSegmentIndex(const uint32_t index);
      pyexport float getCurrentSegmentPrecentage(const float tickPercentage) const;

   private:
      class Header : public Remember::Container
      {
      public:
         Header();
         Header(const Header& other);
         Header& operator=(const Header& other);

      public:
         std::string name;
         uint8_t length;
         Color foregroundColor;
         Color backgroundColor;
      };

      using Headers_ = Remember::RefList<Header>;
      using Division_ = Remember::Value<uint8_t>;
      using SegementCount_ = Remember::Value<uint32_t>;
      using Loop_ = Remember::Value<bool>;

   private:
      Headers_ headers;
      Division_ deafaultDivision;
      SegementCount_ segmentCount;
      Loop_ loop;

      uint32_t currentSegmentIndex;
      Counter divisionCounter;
      bool pastLoop;
      bool firstTickDone;
   };
} // namespace Abstract

#endif // NOT AbstractSegmentCrawlerH
