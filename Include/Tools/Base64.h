#ifndef Base64H
#define Base64H

#include <cinttypes>
#include <vector>

// see https://en.wikipedia.org/wiki/Base64

class Base64
{
public:
   inline static std::vector<uint8_t> encode(const std::vector<uint8_t>& input);
   inline static std::vector<uint8_t> decode(const std::vector<uint8_t>& input);
};

#include "Base64.hpp"

#endif // Base64H
