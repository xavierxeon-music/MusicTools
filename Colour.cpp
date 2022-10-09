#include <Colour.h>

#include <sstream>

const Color Color::Predefined::Black(0, 0, 0);
const Color Color::Predefined::White(255, 255, 255);

const Color Color::Predefined::Red(255, 0, 0);
const Color Color::Predefined::Green(0, 255, 0);
const Color Color::Predefined::Blue(0, 0, 255);

const Color Color::Predefined::Cyan(0, 255, 255);
const Color Color::Predefined::Magenta(255, 0, 255);
const Color Color::Predefined::Yellow(255, 255, 0);

Color::Color(const uint32_t block)
   : value{}
{
   value.block = block;
}

Color::Color(const uint8_t& red, const uint8_t& green, const uint8_t& blue, const uint8_t& alpha)
   : Color()
{
   value.red = red;
   value.green = green;
   value.blue = blue;
   value.alpha = alpha;
}

Color::Color(const std::string& hexString)
   : Color()
{
   value.block = std::stoul(hexString, nullptr, 16);
}

bool Color::operator==(const Color& other) const
{
   return (value.block == other.value.block);
}

bool Color::operator<(const Color& other) const
{
   return (value.block < other.value.block);
}

const uint8_t& Color::red() const
{
   return value.red;
}

const uint8_t& Color::green() const
{
   return value.green;
}

const uint8_t& Color::blue() const
{
   return value.blue;
}

const uint8_t& Color::alpha() const
{
   return value.alpha;
}

float Color::distance(const Color& other) const
{
   float dist = 0.0;
   dist += value.red * other.value.red;
   dist += value.green * other.value.green;
   dist += value.blue * other.value.blue;
   dist += value.alpha * other.value.alpha;
   return dist;
}

Color Color::dim(const float& brightness) const
{
   const float fred = static_cast<float>(value.red) * brightness;
   const float fgreen = static_cast<float>(value.green) * brightness;
   const float fblue = static_cast<float>(value.blue) * brightness;

   const uint8_t red = static_cast<uint8_t>(fred);
   const uint8_t green = static_cast<uint8_t>(fgreen);
   const uint8_t blue = static_cast<uint8_t>(fblue);

   return Color(red, green, blue);
}
