#ifndef AbstractSegmentCrawlerHPP
#define AbstractSegmentCrawlerHPP

#include <Abstract/AbstractSegmentCrawler.h>

// header

Abstract::SegmentCrawler::Header::Header()
   : name()
   , length(0)
   , foregroundColor(fgDefaultColor)
   , backgroundColor(bgDefaultColor)
{
}

Abstract::SegmentCrawler::Header::Header(const Header& other)
   : Header()
{
   *this = other;
}

Abstract::SegmentCrawler::Header& Abstract::SegmentCrawler::Header::operator=(const Header& other)
{
   name = other.name;
   length = other.length;
   foregroundColor = other.foregroundColor;
   backgroundColor = other.backgroundColor;

   return *this;
}

// segment crawler

Abstract::SegmentCrawler::SegmentCrawler()
   : Remember::Container()
   , headers(this)
   , deafaultDivision(this, Tempo::Bar)
   , segmentCount(this, 0)
   , loop(this, false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
}

void Abstract::SegmentCrawler::clear()
{
   deafaultDivision = Tempo::Bar;
   segmentCount = 0;
   headers.clear();

   divisionCounter.setMaxValue(deafaultDivision);

   Remember::Root::setUnsynced();
}

void Abstract::SegmentCrawler::update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount)
{
   deafaultDivision = newDefaultDivision;
   segmentCount = newSegmentCount;

   headers.clear();
   for (uint32_t index = 0; index < segmentCount; index++)
      headers.append(Header());

   divisionCounter.setMaxValue(deafaultDivision);

   Remember::Root::setUnsynced();
}

void Abstract::SegmentCrawler::clockTick()
{
   if (pastLoop)
      return;

   if (!firstTickDone) // ignore the first clock tick
   {
      firstTickDone = true;
      divisionCounter.nextAndIsMaxValue();
      return;
   }

   if (!divisionCounter.nextAndIsMaxValue())
      return;

   currentSegmentIndex++;
   if (currentSegmentIndex == segmentCount)
   {
      if (loop)
         currentSegmentIndex = 0;
      else
         pastLoop = true;
   }
}

void Abstract::SegmentCrawler::clockReset()
{
   divisionCounter.reset();
   currentSegmentIndex = 0;
   pastLoop = false;
}

const uint8_t& Abstract::SegmentCrawler::getDefaultDivision() const
{
   return deafaultDivision.constRef();
}

const uint32_t& Abstract::SegmentCrawler::getSegmentCount() const
{
   return segmentCount.constRef();
}

const std::string& Abstract::SegmentCrawler::getSegmentName(const uint32_t index) const
{
   return headers[index].name;
}

void Abstract::SegmentCrawler::setSegmentName(const uint32_t index, const std::string& name)
{
   headers[index].name = name;
   Remember::Root::setUnsynced();
}

uint8_t Abstract::SegmentCrawler::getSegmentLength(const uint32_t index, bool* isDefault) const
{
   if (0 == headers[index].length)
   {
      if (isDefault)
         *isDefault = true;
      return deafaultDivision.constRef();
   }
   else
   {
      if (isDefault)
         *isDefault = false;
      return headers[index].length;
   }
}

void Abstract::SegmentCrawler::setSegmentLength(const uint32_t index, const uint8_t& length)
{
   headers[index].length = length;
   Remember::Root::setUnsynced();
}

Color Abstract::SegmentCrawler::getSegmentForegroundColor(const uint32_t index, bool* isDefault) const
{
   const Color color = headers[index].foregroundColor;
   if (isDefault)
      *isDefault = (fgDefaultColor == color);

   return color;
}

void Abstract::SegmentCrawler::setSegmentForegroundColor(const uint32_t index, const Color& color)
{
   headers[index].foregroundColor = color;
   Remember::Root::setUnsynced();
}

Color Abstract::SegmentCrawler::getSegmentBackgroundColor(const uint32_t index, bool* isDefault) const
{
   const Color color = headers[index].backgroundColor;
   if (isDefault)
      *isDefault = (bgDefaultColor == color);

   return color;
}

void Abstract::SegmentCrawler::setSegmentBackgroundColor(const uint32_t index, const Color& color)
{
   headers[index].backgroundColor = color;
   Remember::Root::setUnsynced();
}

bool Abstract::SegmentCrawler::isLooping() const
{
   return loop;
}

void Abstract::SegmentCrawler::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
}

const uint32_t& Abstract::SegmentCrawler::getCurrentSegmentIndex() const
{
   return currentSegmentIndex;
}

void Abstract::SegmentCrawler::setCurrentSegmentIndex(const uint32_t index)
{
   currentSegmentIndex = index;
}

uint8_t Abstract::SegmentCrawler::getCurrentSegmentTick() const
{
   return divisionCounter.getCurrentValue();
}

float Abstract::SegmentCrawler::getCurrentSegmentPrecentage(const float tickPercentage) const
{
   float currentTick = divisionCounter.getCurrentValue();
   const float maxTick = divisionCounter.getMaxValue();

   if (currentTick != maxTick && 0.0 < tickPercentage && 1.0 > tickPercentage)
      currentTick += tickPercentage;

   const float percentage = currentTick / maxTick;

   return percentage;
}

#endif // NOT AbstractSegmentCrawlerHPP
