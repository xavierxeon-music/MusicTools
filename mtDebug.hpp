#ifndef mtDebugHPP
#define mtDebugHPP

#include <mtDebug.h>

mtDebug::mtDebug()
   : hasBeenCopied(false)
#ifdef NON_DAISY_DEVICE
   , stream()
#endif // NON_DAISY_DEVICE
{
}

mtDebug::mtDebug(const mtDebug& other)
   : mtDebug()
{
   mtDebug& ref = const_cast<mtDebug&>(other);
   ref.hasBeenCopied = true;

#ifdef NON_DAISY_DEVICE
   stream << other.stream.str();
#endif // NON_DAISY_DEVICE
}

mtDebug::~mtDebug()
{
#ifdef NON_DAISY_DEVICE
   if (!hasBeenCopied)
   {
      std::cout << stream.str() << std::endl;
   }
#endif // NON_DAISY_DEVICE
}

mtDebug& mtDebug::operator<<(const std::string& text)
{
   if (text.empty())
      return *this;

#ifdef NON_DAISY_DEVICE
   stream << text << " ";
#endif // NON_DAISY_DEVICE

   return *this;
}

mtDebug& mtDebug::operator<<(const char* text)
{
   const std::string sText(text);
   return operator<<(sText);
}

template <typename DataType>
mtDebug operator<<(mtDebug dbg, const DataType& value)
{
   dbg << std::to_string(value);
   return dbg;
}

mtDebug operator<<(mtDebug dbg, const bool& value)
{
   if (value)
      dbg << std::string("true");
   else
      dbg << std::string("false");

   return dbg;
}

#endif // NOT mtDebugHPP
