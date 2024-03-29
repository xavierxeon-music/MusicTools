#ifndef SevenBitHPP
#define SevenBitHPP

#include <Tools/SevenBit.h>
#include <cstring>

// modified from https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594

/**
 * The MIT License (MIT)
 * Copyright (c) 2016 tomykaira
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// clang-format off
static constexpr uint8_t encodingTable[] =
{
   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
   'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
   'w', 'x', 'y', 'z', '0', '1', '2', '3',
   '4', '5', '6', '7', '8', '9', '+', '/'
};

static constexpr uint8_t decodingTable[] =
{
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
   52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
   64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
   64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
 };
// clang-format on

std::string SevenBit::encode(const Bytes& input)
{
   const size_t inputLength = input.size();
   if (0 == inputLength)
      return std::string();

   const size_t outputLength = 4 * ((inputLength + 2) / 3);

   Bytes base64;
   base64.resize(outputLength);

   size_t j = 0;
   auto addToOutput = [&](const uint8_t& encodingIndex)
   {
      base64[j] = encodingTable[encodingIndex];
      j++;
   };

   auto addPadding = [&]()
   {
      base64[j] = 0x3d; // append =
      j++;
   };

   size_t i = 0;
   while (i < inputLength - 2) // process 4 byte blocks
   {
      addToOutput((input[i] >> 2) & 0x3F);
      addToOutput(((input[i] & 0x3) << 4) | ((input[i + 1] & 0xF0) >> 4));
      addToOutput(((input[i + 1] & 0xF) << 2) | ((input[i + 2] & 0xC0) >> 6));
      addToOutput(input[i + 2] & 0x3F);

      i += 3;
   }

   if (i < inputLength) // there might be some input bytes left
   {
      addToOutput((input[i] >> 2) & 0x3F);

      if (i == (inputLength - 1))
      {
         addToOutput(((input[i] & 0x3) << 4));
         addPadding();
      }
      else
      {
         addToOutput(((input[i] & 0x3) << 4) | ((input[i + 1] & 0xF0) >> 4));
         addToOutput(((input[i + 1] & 0xF) << 2));
      }
      addPadding();
   }

   std::string output(base64.begin(), base64.end());
   return output;
}

Bytes SevenBit::decode(const std::string& input)
{
   Bytes base64(input.size(), 0);
   std::memcpy(base64.data(), input.data(), input.size());

   size_t inputLength = input.size();
   if (0 == inputLength || inputLength % 4 != 0)
      return Bytes();

   size_t outputLength = inputLength / 4 * 3;

   // discard eventual padding
   if (base64[inputLength - 1] == '=')
      outputLength--;
   if (base64[inputLength - 2] == '=')
      outputLength--;

   Bytes output;
   output.resize(outputLength);

   size_t i = 0;
   size_t j = 0;
   while (i < inputLength)
   {
      auto getNextInputByte = [&]() -> uint8_t
      {
         if (base64[i] == '=') // end padding
         {
            i++;
            return 0;
         }
         else
         {
            const uint8_t index = base64[i];
            i++;
            return decodingTable[index];
         }
      };

      uint32_t a = getNextInputByte();
      uint32_t b = getNextInputByte();
      uint32_t c = getNextInputByte();
      uint32_t d = getNextInputByte();

      uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

      auto setOutputByte = [&](const uint8_t& value)
      {
         if (j >= outputLength)
            return;

         output[j] = value;
         j++;
      };

      setOutputByte((triple >> 2 * 8) & 0xFF);
      setOutputByte((triple >> 1 * 8) & 0xFF);
      setOutputByte((triple >> 0 * 8) & 0xFF);
   }

   return output;
}

#endif // SevenBitHPP
