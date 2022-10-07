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
   bool copied;
#ifdef NON_DAISY_DEVICE
   std::ostringstream stream;
#endif // NON_DAISY_DEVICE
};

inline debug operator<<(debug dbg, const uint8_t& value);
inline debug operator<<(debug dbg, const bool& value);
inline debug operator<<(debug dbg, const float& value);

#ifndef debugHPP
#include "../debug.hpp"
#endif // NOT debugHPP

#endif // NOT debugH
