#ifndef TextH
#define TextH

#include <string>

struct Text
{
   inline static std::string convert(const bool& value);
   inline static std::string convert(const int& value);
   inline static std::string convert(const uint8_t& value);
   inline static std::string convert(const uint32_t& value);
   inline static std::string convert(const uint64_t& value);
   inline static std::string convert(const float& value, const uint8_t& decimalPlaces = 2);

   inline static std::string pad(const std::string& text, uint8_t numberOfDigits, const std::string& padChar = "0");
};

#ifndef TextHPP
#include "../../Text.hpp"
#endif // TextHPP

#endif // TextH
