#ifndef RangeHPP
#define RangeHPP

#include <Tools/Range.h>

#include <limits>
#include <type_traits>

// Mapper

template <typename DataType>
Range::Finder<DataType>::Finder()
   : minValue()
   , maxValue()
{
   reset();
}

template <typename DataType>
void Range::Finder<DataType>::reset()
{
   minValue = std::numeric_limits<DataType>::max();

   if (std::is_signed<DataType>::value)
      maxValue = DataType(0);
   else
      maxValue = -std::numeric_limits<DataType>::max();
}

template <typename DataType>
void Range::Finder<DataType>::init(const DataType& value)
{
   minValue = value;
   maxValue = value;
}

template <typename DataType>
void Range::Finder<DataType>::observe(const DataType& value)
{
   if (value < minValue)
      minValue = value;
   if (value > maxValue)
      maxValue = value;
}

template <typename DataType>
const DataType& Range::Finder<DataType>::min() const
{
   return minValue;
}

template <typename DataType>
const DataType& Range::Finder<DataType>::max() const
{
   return maxValue;
}

template <typename DataType>
DataType Range::Finder<DataType>::diff() const
{
   return maxValue - minValue;
}

template <typename DataType>
template <typename TestType, std::enable_if_t<std::is_integral<TestType>::value, bool>>
size_t Range::Finder<DataType>::length() const
{
   return 1 + (maxValue - minValue);
}

template <typename DataType>
template <typename TestType, std::enable_if_t<std::is_integral<TestType>::value, bool>>
DataType Range::Finder<DataType>::value(const size_t index) const
{
   if (index >= length())
      return maxValue;

   return minValue + index;
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

   if (0.0 >= diffInput || 0.0 >= diffOutput)
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
