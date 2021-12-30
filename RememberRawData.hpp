#ifndef RememberRawDataHPP
#define RememberRawDataHPP

#include <Storage/Private/RememberRawData.h>

#include <cstring>

Remember::RawData::RawData(uint8_t* bytes, size_t size)
   : content()
{
   if (0 < size)
   {
      content.resize(size, 0);
      memcpy(content.data(), bytes, size);
   }
}

template <typename DataType>
void Remember::RawData::append(const DataType& value)
{
   union
   {
      uint8_t out[sizeof(DataType)];
      DataType in;
   } convert;

   convert.in = value;

   for (size_t index = 0; index < sizeof(DataType); index++)
      content.push_back(convert.out[index]);
}

template <typename DataType>
void Remember::RawData::copyToValue(DataType& value, size_t& cursor) const
{
   union
   {
      uint8_t in[sizeof(DataType)];
      DataType out;
   } convert;

   for (size_t index = 0; index < sizeof(DataType); index++)
      convert.in[index] = content[cursor + index];

   value = convert.out;
   cursor += sizeof(DataType);
}

const Remember::RawData::Content& Remember::RawData::getContent() const
{
   return content;
}

#endif // RememberRawDataHPP
