#ifndef RememberRawDataH
#define RememberRawDataH

#include <MusicTools.h>

namespace Remember
{
   class RawData
   {
   public:
      using Content = std::vector<uint8_t>;

   public:
      inline RawData(uint8_t* bytes = nullptr, size_t size = 0);

   public:
      // clang-format off
      template <typename DataType> void append(const DataType& value);
      template <typename DataType> void copyToValue(DataType& value, size_t& cursor) const;
      // clang-format on
      inline const Content& getContent() const;

   private:
      Content content;
   };
} // namespace Remember

#include <RememberRawData.hpp>

#endif //  RememberRawDataH
