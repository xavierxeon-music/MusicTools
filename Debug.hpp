#ifndef debugHPP
#define debugHPP

#include <Debug.h>

debug::debug()
   : hasBeenCopied(false)
#ifdef NON_DAISY_DEVICE
   , stream()
#endif // NON_DAISY_DEVICE
{
}

debug::debug(const debug& other)
   : debug()
{
   debug& ref = const_cast<debug&>(other);
   ref.hasBeenCopied = true;

#ifdef NON_DAISY_DEVICE
   stream << other.stream.str();
#endif // NON_DAISY_DEVICE
}

debug::~debug()
{
#ifdef NON_DAISY_DEVICE
   if (!hasBeenCopied)
   {
      std::cout << stream.str() << std::endl;
   }
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

template <typename DataType>
debug operator<<(debug dbg, const DataType& value)
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

#endif // NOT debugHPP
