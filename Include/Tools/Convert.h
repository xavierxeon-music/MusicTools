#ifndef ConvertH
#define ConvertH

#include <string>

struct Convert
{
   inline static std::string text(const bool& value);
   inline static std::string text(const int& value);
   inline static std::string text(const uint8_t& value);
   inline static std::string text(const uint32_t& value);
   inline static std::string text(const uint64_t& value);
   inline static std::string text(const float& value, const uint8_t& decimalPlaces = 2);

   inline static uint16_t compileDigitCount(uint64_t number);
};

#ifndef ConvertHPP
#include "../../Convert.hpp"
#endif // ConvertHPP

#endif // ConvertH
