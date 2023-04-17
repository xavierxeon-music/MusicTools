#ifndef MelodiesH
#define MelodiesH

#include <Abstract/AbstractSegmentCrawler.h>

class Melodies : public virtual Abstract::SegmentCrawler
{
public:
   inline Melodies();

public:
   inline virtual void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override;
   inline virtual void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override;
};

#ifndef MelodiesHPP
#include "../../Melodies.hpp"
#endif // NOT MelodiesHPP

#endif // NOT MelodiesH
