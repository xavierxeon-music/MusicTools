#ifndef debugHPP
#define debugHPP

#include <debug.h>

debug::debug()
   : copied(false)
#ifdef NON_DAISY_DEVICE
   , stream()
#endif // NON_DAISY_DEVICE
{
}

debug::debug(const debug& other)
   : debug()
{
#ifdef NON_DAISY_DEVICE
   stream << other.stream.str();
#endif // NON_DAISY_DEVICE

   debug& origin = const_cast<debug&>(other);
   origin.copied = true;
}

debug::~debug()
{
#ifdef NON_DAISY_DEVICE
   if (!copied)
      std::cout << stream.str() << std::endl;
#endif // NON_DAISY_DEVICE
}

debug& debug::operator<<(const std::string& text)
{
   if (text.empty())
      return *this;

#ifdef NON_DAISY_DEVICE
   stream << text << " ";
#endif // NON_DAISY_DEVICE

   return *this;
}

debug& debug::operator<<(const char* text)
{
   const std::string sText(text);
   return operator<<(sText);
}

debug operator<<(debug dbg, const uint8_t& value)
{
   dbg << std::to_string(value);
   return dbg;
}

debug operator<<(debug dbg, const bool& value)
{
   if (value)
      dbg << std::string("true");
   else
      dbg << std::string("false");

   return dbg;
}

debug operator<<(debug dbg, const float& value)
{
   dbg << std::to_string(value);
   return dbg;
}

#endif // NOT debugHPP
