#ifndef SevenBitH
#define SevenBitH

#include <MusicTools.h>

// see https://en.wikipedia.org/wiki/SevenBit

class SevenBit
{
public:
   inline static std::vector<uint8_t> encode(const std::vector<uint8_t>& input);
   inline static std::vector<uint8_t> decode(const std::vector<uint8_t>& input);
};

#include "SevenBit.hpp"

#endif // SevenBitH
