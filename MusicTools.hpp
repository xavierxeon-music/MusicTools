#ifndef MusicToolsHPP
#define MusicToolsHPP

#include <MusicTools.h>

Bytes& operator<<(Bytes& data, const uint8_t& byte)
{
   data.push_back(byte);
   return data;
}

#ifndef NON_DAISY_DEVICE

void print(const Bytes& data, bool withAscii)
{
   (void)data;
   (void)withAscii;
}

#else

#include <bitset>
#include <iostream>

void print(const Bytes& data, bool withAscii)
{
   for (const uint8_t byte : data)
   {
      std::cout << "0x" << std::hex << static_cast<uint16_t>(byte) << std::dec;
      std::cout << " ";
      std::cout << std::bitset<8>(byte);
      if (withAscii)
      {
         std::cout << " ";
         std::cout << byte;
      }
      std::cout << std::endl;
   }
   std::cout << data.size() << std::endl;
}
#endif

template <typename DataType>
void mergeVectors(std::vector<DataType>& data, const std::vector<DataType>& other)
{
   data.insert(data.end(), other.cbegin(), other.cend());
}

#endif // MusicToolsHPP
