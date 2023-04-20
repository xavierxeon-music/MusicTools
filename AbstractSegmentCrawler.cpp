#include <Abstract/AbstractSegmentCrawler.h>

// header

Abstract::SegmentCrawler::Header::Header()
   : name()
   , length(0)
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

   return *this;
}

// segment crawler

Abstract::SegmentCrawler::SegmentCrawler()
   : headers()
   , defaultLength(Tempo::Bar)
   , segmentCount(0)
   , loop(false)
   , currentSegmentIndex(0)
   , divisionCounter(1)
   , pastLoop(false)
   , firstTickDone(false)
{
}

void Abstract::SegmentCrawler::clear()
{
   defaultLength = Tempo::Bar;
   segmentCount = 0;
   headers.clear();

   divisionCounter.setMaxValue(defaultLength);
}

void Abstract::SegmentCrawler::update(const Tempo::Tick& newDefaultLength, const uint32_t newSegmentCount)
{
   defaultLength = newDefaultLength;
   segmentCount = newSegmentCount;

   while (headers.size() > newSegmentCount)
      headers.remove(headers.size() - 1);
   while (headers.size() < newSegmentCount)
      headers.append(Header());

   divisionCounter.setMaxValue(defaultLength);
}

void Abstract::SegmentCrawler::clockTick()
{
   if (0 == getSegmentCount())
      return;

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
   if (currentSegmentIndex >= segmentCount)
   {
      if (loop)
         currentSegmentIndex = 0;
      else
         pastLoop = true;
   }

   divisionCounter.setMaxValue(getSegmentLength(currentSegmentIndex));
}

void Abstract::SegmentCrawler::clockReset()
{
   divisionCounter.reset();
   currentSegmentIndex = 0;
   pastLoop = false;
}

const Tempo::Tick& Abstract::SegmentCrawler::getDefaultLength() const
{
   return defaultLength;
}

const uint32_t& Abstract::SegmentCrawler::getSegmentCount() const
{
   return segmentCount;
}

const std::string& Abstract::SegmentCrawler::getSegmentName(const uint32_t index) const
{
   return headers[index].name;
}

void Abstract::SegmentCrawler::setSegmentName(const uint32_t index, const std::string& name)
{
   headers[index].name = name;
}

Tempo::Tick Abstract::SegmentCrawler::getSegmentLength(const uint32_t index, bool* isDefault) const
{
   if (0 == headers[index].length)
   {
      if (isDefault)
         *isDefault = true;
      return defaultLength;
   }
   else
   {
      if (isDefault)
         *isDefault = false;
      return headers[index].length;
   }
}

void Abstract::SegmentCrawler::setSegmentLength(const uint32_t index, const Tempo::Tick &length)
{
   headers[index].length = length;
   if (index == currentSegmentIndex)
   {
      divisionCounter.setMaxValue(length);
   }
}

bool Abstract::SegmentCrawler::isLooping() const
{
   return loop;
}

bool Abstract::SegmentCrawler::isPastLoop() const
{
   return loop ? false : pastLoop;
}

void Abstract::SegmentCrawler::setLooping(bool on)
{
   loop = on;
}

const uint32_t& Abstract::SegmentCrawler::getCurrentSegmentIndex() const
{
   static const uint32_t zero = 0;
   if (pastLoop)
      return zero;

   return currentSegmentIndex;
}

void Abstract::SegmentCrawler::setCurrentSegmentIndex(const uint32_t index)
{
   currentSegmentIndex = index;
}

uint8_t Abstract::SegmentCrawler::getCurrentSegmentTick() const
{
   static const uint32_t zero = 0;
   if (pastLoop)
      return zero;

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

void Abstract::SegmentCrawler::updateProxies()
{
   // do nothing
}
