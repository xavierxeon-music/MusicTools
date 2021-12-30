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
};

#include <Convert.hpp>

#endif // ConvertH
