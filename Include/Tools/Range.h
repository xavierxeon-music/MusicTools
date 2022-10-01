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
      void reset();                     // mint to datatype max and max to datatype min
      void init(const DataType& value); // min and max to value
      void observe(const DataType& value);
      const DataType& getMinValue() const;
      const DataType& getMaxValue() const;

   private:
      DataType min;
      DataType max;
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
