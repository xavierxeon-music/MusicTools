#ifndef MusicToolsHPP
#define MusicToolsHPP

#include <MusicTools.h>

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

#endif // MusicToolsHPP
