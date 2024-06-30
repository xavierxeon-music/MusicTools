#ifndef mtDebugH
#define mtDebugH

#include <string>

#ifdef NON_DAISY_DEVICE
#include <iostream>
#include <sstream>
#endif // NON_DAISY_DEVICE

class mtDebug
{
public:
   inline mtDebug();
   inline mtDebug(const mtDebug& other);
   inline ~mtDebug();

public:
   inline mtDebug& operator<<(const std::string& text);
   inline mtDebug& operator<<(const char* text);

private:
   bool hasBeenCopied;
#ifdef NON_DAISY_DEVICE
   std::ostringstream stream;
#endif // NON_DAISY_DEVICE
};

template <typename DataType>
mtDebug operator<<(mtDebug dbg, const DataType& value);

inline mtDebug operator<<(mtDebug dbg, const bool& value);

#ifndef mtDebugHPP
#include "../mtDebug.hpp"
#endif // NOT mtDebugHPP

#endif // NOT mtDebugH
