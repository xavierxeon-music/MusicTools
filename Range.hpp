#ifndef RangeHPP
#define RangeHPP

#include <Tools/Range.h>

#include <limits>
#include <type_traits>

// Mapper

template <typename DataType>
Range::Finder<DataType>::Finder()
   : min()
   , max()
{
   reset();
}

template <typename DataType>
void Range::Finder<DataType>::reset()
{
   min = std::numeric_limits<DataType>::max();

   if (std::is_signed<DataType>::value)
      max = DataType(0);
   else
      max = -std::numeric_limits<DataType>::max();
}

template <typename DataType>
void Range::Finder<DataType>::observe(const DataType& value)
{
   if (value < min)
      min = value;
   if (value > max)
      max = value;
}

template <typename DataType>
const DataType& Range::Finder<DataType>::getMinValue() const
{
   return min;
}

template <typename DataType>
const DataType& Range::Finder<DataType>::getMaxValue() const
{
   return max;
}

// Mapper

Range::Mapper::Mapper(const float& minInput, const float& maxInput, const float& minOutput, const float& maxOutput)
   : minInput(minInput)
   , maxInput(maxInput)
   , minOutput(minOutput)
   , maxOutput(maxOutput)
{
   updateScale();
}

void Range::Mapper::setMinInput(const float& value)
{
   if (value < maxInput)
   {
      minInput = value;
      updateScale();
   }
}

void Range::Mapper::setMaxInput(const float& value)
{
   if (value > minInput)
   {
      maxInput = value;
      updateScale();
   }
}

void Range::Mapper::setMinOutput(const float& value)
{
   minOutput = value;
   updateScale();
}

void Range::Mapper::setMaxOutput(const float& value)
{
   maxOutput = value;
   updateScale();
}

void Range::Mapper::updateScale()
{
   const float diffOutput = maxOutput - minOutput;
   const float diffInput = maxInput - minInput;

   if (0.0 == diffInput || 0.0 == diffOutput)
   {
      scale = 0.0;
   }
   else
   {
      scale = diffOutput / diffInput;
   }
}

float Range::Mapper::operator()(const float& input) const
{
   if (input <= minInput)
      return minOutput;
   if (input >= maxInput)
      return maxOutput;

   const float diff = input - minInput;
   const float output = minOutput + (diff * scale);

   return output;
}

// Other

template <typename DataType>
const DataType& Range::clamp(const DataType& value, const DataType& min, const DataType& max)
{
   if (value < min)
      return min;
   if (value > max)
      return max;

   return value;
}

template <typename DataType>
const DataType& Range::min(const DataType& value1, const DataType& value2)
{
   if (value1 < value2)
      return value1;

   return value2;
}

template <typename DataType>
const DataType& Range::max(const DataType& value1, const DataType& value2)
{
   if (value1 < value2)
      return value2;

   return value1;
}

#endif // RangeHPP
