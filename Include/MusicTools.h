#ifndef MusicToolsH
#define MusicToolsH

#include <cinttypes>
#include <string>
#include <vector>

#include "debug.h"

// used to auto geenrate python bindings
// must be at start of namespce, class, sub class, sub struct, function or enum
#define pyexport

// byte sized data
using Bytes = std::vector<uint8_t>;
inline Bytes& operator<<(Bytes& data, const uint8_t& byte);
inline void print(const Bytes& data, bool withAscii = false);

// float sized data, for example audio buffer
using Data = std::vector<float>;

template <typename DataType>
void mergeVectors(std::vector<DataType>& data, const std::vector<DataType>& other);

/// color
struct Color
{
   uint8_t red;
   uint8_t green;
   uint8_t blue;

   inline bool operator==(const Color& other) const;
};

// optional compiler tests
template <typename TestType>
using isIntegerType = typename std::enable_if<std::is_integral<TestType>::value, bool>::type;

template <typename TestType>
using isFloatType = typename std::enable_if<std::is_floating_point<TestType>::value, bool>::type;

template <typename TestType>
using isSigned = typename std::enable_if<std::is_signed<TestType>::value, bool>::type;

template <typename TestType>
using isUnsigned = typename std::enable_if<!std::is_signed<TestType>::value, bool>::type;

#ifndef MusicToolsHPP
#include "../MusicTools.hpp"
#endif // NOT MusicToolsHPP

#endif // NOT MusicToolsH
