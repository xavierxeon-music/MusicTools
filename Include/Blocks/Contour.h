#ifndef ContourH
#define ContourH

#include <Abstract/AbstractSegmentCrawler.h>

pyexport class Contour : public Remember::Container
{
public:
   class Poly;

public:
   pyexport inline Contour();
   inline Contour(const Contour& other);
   inline Contour& operator=(const Contour& other);

public:
   pyexport inline void setup(Poly* poly);
   pyexport inline void resize(const uint32_t segmentCount, bool clearContent);

   pyexport inline std::string getName() const;
   pyexport inline void setName(const std::string& text);

   pyexport inline uint8_t getSegmentValue(const uint32_t index, const float& segmentPercentage) const;

   pyexport inline void resetSegment(const uint32_t index);

   pyexport inline uint8_t getSegmentStartValue(const uint32_t index) const;
   pyexport inline bool hasSegmentStartValue(const uint32_t index) const;
   pyexport inline void setSegmentStartValue(const uint32_t index, const uint8_t value);

   pyexport inline uint8_t getSegmentEndValue(const uint32_t index) const;
   pyexport inline bool hasSegmentEndValue(const uint32_t index) const;
   pyexport inline void setSegmentEndValue(const uint32_t index, const uint8_t value);

   pyexport inline bool hasSegmentValues(const uint32_t index) const;

   pyexport inline bool isSegmentSteady(const uint32_t index) const;
   pyexport inline void setSegmentSteady(const uint32_t index, bool on);

private:
   using Name_ = Remember::String;
   using Value_ = Remember::Value<uint8_t>;
   using Bool_ = Remember::Value<bool>;

   struct Segment : public Remember::Container
   {
      Value_ startValue;
      Bool_ startExists;

      Value_ endValue;
      Bool_ endExists;

      Bool_ steady;

      inline Segment();
      inline Segment(const Segment& other);
      inline Segment& operator=(const Segment& other);
   };

   using Segments_ = Remember::RefList<Segment>;

   struct Proxy
   {
      uint8_t startValue = 0;
      uint8_t endValue = 0;

      using List = std::vector<Proxy>;
   };

private:
   inline void updateProxyList() const;

private:
   Poly* poly;

   Name_ name;
   Segments_ segments;

   mutable bool dirty;
   mutable Proxy::List proxyList;
};

pyexport class Contour::Poly : public virtual Abstract::SegmentCrawler
{
public:
   static constexpr uint8_t contourCount = 16;

public:
   pyexport inline Poly();

public:
   pyexport inline virtual void clear() override;
   pyexport inline virtual void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override;

   pyexport inline uint8_t getContourCount() const;
   pyexport inline Contour& getContour(const uint8_t contourIndex);
   inline const Contour& getConstContour(const uint8_t contourIndex) const;

private:
   using Contours_ = Remember::RefArray<Contour, contourCount>;

private:
   Contours_ contours;
};

#ifndef ContourHPP
#include "../../Contour.hpp"
#endif // NOT ContourHPP

#endif // NOT ContourH
