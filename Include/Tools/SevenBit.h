#ifndef SevenBitH
#define SevenBitH

#include <MusicTools.h>

// see https://en.wikipedia.org/wiki/SevenBit

class SevenBit
{
public:
   inline static Bytes encode(const Bytes& input);
   inline static Bytes decode(const Bytes& input);
};

#ifndef SevenBitHPP
#include "../../SevenBit.hpp"
#endif // NOT SevenBitHPP

#endif // NOT SevenBitH
