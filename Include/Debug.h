#ifndef debugH
#define debugH

#include <string>

#ifdef NON_DAISY_DEVICE
#include <iostream>
#include <sstream>
#endif // NON_DAISY_DEVICE

class debug
{
public:
   inline debug();
   inline debug(const debug& other);
   inline ~debug();

public:
   inline debug& operator<<(const std::string& text);
   inline debug& operator<<(const char* text);

private:
   uint8_t refCount;
   bool hasBeenCopied;
#ifdef NON_DAISY_DEVICE
   std::ostringstream stream;
#endif // NON_DAISY_DEVICE
};

template <typename DataType>
debug operator<<(debug dbg, const DataType& value);

inline debug operator<<(debug dbg, const bool& value);

#ifndef debugHPP
#include "../Debug.hpp"
#endif // NOT debugHPP

#endif // NOT debugH
