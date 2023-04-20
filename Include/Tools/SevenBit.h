#ifndef SevenBitH
#define SevenBitH

#include <MusicTools.h>

// see https://en.wikipedia.org/wiki/Base64

class SevenBit
{
public:
   inline static std::string encode(const Bytes& input);
   inline static Bytes decode(const std::string& input);
};

#ifndef SevenBitHPP
#include "../../SevenBit.hpp"
#endif // NOT SevenBitHPP

#endif // NOT SevenBitH
