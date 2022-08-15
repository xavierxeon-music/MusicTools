#ifndef SevenBitH
#define SevenBitH

#include <MusicTools.h>

// see https://en.wikipedia.org/wiki/Base64

pyexport class SevenBit
{
public:
   pyexport inline static std::string encode(const Bytes& input);
   pyexport inline static Bytes decode(const std::string& input);
};

#ifndef SevenBitHPP
#include "../../SevenBit.hpp"
#endif // NOT SevenBitHPP

#endif // NOT SevenBitH
