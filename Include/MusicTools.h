#ifndef MusicToolsH
#define MusicToolsH

#include <cinttypes>
#include <string>
#include <vector>

using Bytes = std::vector<uint8_t>;

inline Bytes& operator<<(Bytes& data, const uint8_t& byte);

inline void print(const Bytes& data, bool withAscii = false);

#include "MusicTools.hpp"

#endif // MusicToolsH
