#ifndef MusicToolsH
#define MusicToolsH

#include <cinttypes>
#include <string>
#include <vector>

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
void mergeVectos(std::vector<DataType>& data, const std::vector<DataType>& other);

#ifdef NON_DAISY_DEVICE
#define DSY_SDRAM_BSS
#else
#include <dev/sdram.h>
#endif //  NON_DAISY_DEVICE

#ifndef MusicToolsHPP
#include "../MusicTools.hpp"
#endif // NOT MusicToolsHPP

#endif // NOT MusicToolsH
