// can not be named color, as that file is a system file!
#ifndef ColourH
#define ColourH

#include <cinttypes>
#include <string>

class Color
{
public:
   struct Predefined
   {
      static const Color black;
      static const Color white;

      static const Color red;
      static const Color green;
      static const Color blue;

      static const Color cyan;
      static const Color magenta;
      static const Color yellow;
   };

public:
   Color(const uint32_t block = 0);
   Color(const uint8_t& red, const uint8_t& green, const uint8_t& blue, const uint8_t& alpha = 0);
   Color(const std::string& hexString);

public:
   bool operator==(const Color& other) const;
   const uint8_t& red() const;
   const uint8_t& green() const;
   const uint8_t& blue() const;
   const uint8_t& alpha() const;
   float distance(const Color& other);
   Color dim(const float& brightness) const;

private:
   union Value
   {
      struct
      {
         uint8_t alpha;
         uint8_t red;
         uint8_t green;
         uint8_t blue;
      };
      uint32_t block;
   };

private:
   Value value;
};

#endif // NOT ColourH
