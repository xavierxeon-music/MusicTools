#ifndef MusicToolsH
#define MusicToolsH

#include <cinttypes>
#include <string>
#include <vector>

// used to auto geenrate python bindings
// must be at start of sub class, sub struct, function or eneum
#define pyexport

// OPTIONAL: marks the class name to be used in a python binding, one per file
#define PYCLASS(text)

// OPTIONAL: add namespace to pyuthon name, one per file
#define PYNAMESPCE(text)

// byte sized data
using Bytes = std::vector<uint8_t>;
inline Bytes& operator<<(Bytes& data, const uint8_t& byte);
inline void print(const Bytes& data, bool withAscii = false);

// float sized data, for example audio buffer
using Data = std::vector<float>;

#ifndef MusicToolsHPP
#include "../MusicTools.hpp"
#endif // NOT MusicToolsHPP

#endif // NOT MusicToolsH
