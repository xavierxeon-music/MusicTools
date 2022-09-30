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
      pyexport inline SegmentCrawler();

   public:
      pyexport inline virtual void clear();
      pyexport inline virtual void update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount);

      pyexport inline void clockTick();
      pyexport inline void clockReset();

      pyexport inline const uint8_t& getDefaultDivision() const;
      pyexport inline const uint32_t& getSegmentCount() const;
      pyexport inline uint8_t getSegmentLength(const uint32_t index) const;

      pyexport inline bool isLooping() const;
      pyexport inline void setLooping(bool on);

      pyexport inline const uint32_t& getCurrentSegmentIndex() const;
      pyexport inline uint8_t getCurrentSegmentTick() const;
      pyexport inline void setCurrentSegmentIndex(const uint32_t index);
      pyexport inline float getCurrentSegmentPrecentage(const float tickPercentage) const;

   private:
      using Division_ = Remember::Value<uint8_t>;
      using SegementCount_ = Remember::Value<uint32_t>;
      using Loop_ = Remember::Value<bool>;

   private:
      Division_ deafaultDivision;
      SegementCount_ segmentCount;
      Loop_ loop;

      uint32_t currentSegmentIndex;
      Counter divisionCounter;
      bool pastLoop;
      bool firstTickDone;
   };
} // namespace Abstract

#ifndef AbstractSegmentCrawlerHPP
#include "../../AbstractSegmentCrawler.hpp"
#endif // NOT AbstractSegmentCrawlerHPP

#endif // NOT AbstractSegmentCrawlerH
