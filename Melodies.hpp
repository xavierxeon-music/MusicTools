#ifndef MelodiesHPP
#define MelodiesHPP

#include <Blocks/Melodies.h>

Melodies::Melodies()
   : Abstract::SegmentCrawler()

{
}

void Melodies::update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount)
{
   Abstract::SegmentCrawler::update(newDefaultDivision, newSegmentCount);
}

void Melodies::setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length)
{
   Abstract::SegmentCrawler::setSegmentLength(segmentIndex, length);
}

#endif // NOT MelodiesHPP
