#ifndef TextHPP
#define TextHPP

#include <Tools/Text.h>

#include <cmath>

std::string Text::convert(const bool& value)
{
   if (value)
      return "True";
   else
      return "False";
}

std::string Text::convert(const int& value)
{
   return std::to_string(value);
}

std::string Text::convert(const uint8_t& value)
{
   return std::to_string(value);
}

std::string Text::convert(const uint32_t& value)
{
   return std::to_string(value);
}

std::string Text::convert(const uint64_t& value)
{
   return std::to_string(value);
}

std::string Text::convert(const float& value, const uint8_t& decimalPlaces)
{
   bool isNegative = (0 > value);
   const float factor = std::pow(10.0f, decimalPlaces);

   const long int iValue = static_cast<long int>(factor * (isNegative ? -value : value));
   std::string text = std::to_string(iValue);

   if (0 == decimalPlaces)
      return text;

   if (text.size() > decimalPlaces)
   {
      text.insert(text.size() - decimalPlaces, ".");
   }
   else
   {
      while (text.size() < decimalPlaces)
         text = "0" + text;
      text = "0." + text;
   }
   if (isNegative)
      text = "-" + text;

   return text;
}

std::string Text::pad(const std::string& text, uint8_t numberOfDigits, const std::string& padChar)
{
   std::string outText = text;
   while (numberOfDigits > outText.size())
      outText = padChar + outText;

   return outText;
}

#endif // TextHPP
