// can not be named color, as that file is a system file!
#ifndef ColourH
#define ColourH

#include <cinttypes>
#include <string>

#include "mtDebug.h"

class Color
{
public:
   struct Predefined
   {
      static const Color Black;
      static const Color White;

      static const Color Red;
      static const Color Green;
      static const Color Blue;

      static const Color Cyan;
      static const Color Magenta;
      static const Color Yellow;
   };

public:
   Color(const uint32_t block = 0);
   Color(const uint8_t& red, const uint8_t& green, const uint8_t& blue, const uint8_t& alpha = 0);
   Color(const std::string& hexString);
   Color(const Color& other);
   Color& operator=(const Color& other);

public:
   bool operator==(const Color& other) const;
   bool operator<(const Color& other) const;
   const uint8_t& red() const;
   const uint8_t& green() const;
   const uint8_t& blue() const;
   const uint8_t& alpha() const;
   float distance(const Color& other) const;
   Color dim(const float& brightness) const;

private:
   union Value
   {
      struct // order matters!
      {
         uint8_t blue;
         uint8_t green;
         uint8_t red;
         uint8_t alpha;
      };
      uint32_t block;
   };

private:
   Value value;
};

mtDebug operator<<(mtDebug dbg, const Color& color);

#endif // NOT ColourH
