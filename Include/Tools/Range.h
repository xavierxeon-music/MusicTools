#ifndef RangeH
#define RangeH

#include <MusicTools.h>

struct Range
{
   template <typename DataType>
   class Finder
   {
   public:
      Finder();

   public:
      /// min to datatype max and max to datatype min
      template <typename TestType = DataType, isSigned<TestType> = true>
      void reset();

      /// min to zero and max to datatype min
      template <typename TestType = DataType, isUnsigned<TestType> = true>
      void reset();

      /// min and max to value
      void init(const DataType& value);

      /// test value and update min / mix
      void observe(const DataType& value);

      const DataType& min() const;
      const DataType& max() const;
      DataType diff() const;

      // only for integer types
      template <typename TestType = DataType, isIntegerType<TestType> = true>
      size_t length() const;

      template <typename TestType = DataType, isIntegerType<TestType> = true>
      DataType value(const size_t index) const;

   private:
      DataType minValue;
      DataType maxValue;
   };

   class Mapper
   {
   public:
      inline Mapper(const float& minInput, const float& maxInput, const float& minOutput, const float& maxOutput);

   public:
      inline float operator()(const float& input) const;

      inline void setMinInput(const float& value);
      inline void setMaxInput(const float& value);
      inline void setMinOutput(const float& value);
      inline void setMaxOutput(const float& value);

   private:
      inline void updateScale();

   private:
      float minInput;
      float maxInput;
      float minOutput;
      float maxOutput;
      float scale;
   };

   template <typename DataType>
   static const DataType& clamp(const DataType& value, const DataType& min, const DataType& max);

   template <typename DataType>
   static const DataType& min(const DataType& value1, const DataType& value2);

   template <typename DataType>
   static const DataType& max(const DataType& value1, const DataType& value2);
};

#ifndef RangeHPP
#include "../../Range.hpp"
#endif // NOT RangeHPP

#endif // NOT RangeH
