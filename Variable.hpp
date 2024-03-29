#ifndef VariableHPP
#define VariableHPP

#include <cassert>

#include <Tools/Variable.h>

// Optional

template <typename Type>
Variable::Optional<Type>::Optional()
   : value(Type(0))
   , set(false)
{
}

template <typename Type>
Type& Variable::Optional<Type>::oparator()
{
   return value;
}

template <typename Type>
const Type& Variable::Optional<Type>::oparator() const
{
   return value;
}

template <typename Type>
Variable::Optional<Type>& Variable::Optional<Type>::operator=(const Type& otherValue)
{
   value = otherValue;
   set = true;
}

template <typename Type>
bool Variable::Optional<Type>::hasValue() const
{
   return set;
}

// Integer

template <typename IntegerType, IntegerType diffValue>
Variable::Integer<IntegerType, diffValue>::Integer(IntegerType& variable, const IntegerType& minValue, const IntegerType& maxValue, const bool wrap)
   : variable(variable)
   , minValue(minValue)
   , maxValue(maxValue)
   , wrap(wrap)
{
   static_assert(std::is_integral<IntegerType>::value, "type must be an integer");
   static_assert(diffValue >= 1, "DiffValue must be positive");

   assert(minValue < maxValue);
   assert(diffValue <= maxValue - minValue);
}

template <typename IntegerType, IntegerType diffValue>
bool Variable::Integer<IntegerType, diffValue>::change(bool up)
{
   if (up)
      return increment();
   else
      return decrement();
}

template <typename IntegerType, IntegerType diffValue>
bool Variable::Integer<IntegerType, diffValue>::increment()
{
   if (maxValue == variable)
   {
      if (!wrap)
         return false;
      else
         variable = minValue;
   }
   else
   {
      if (variable + diffValue > maxValue)
         variable = maxValue;
      else
         variable += diffValue;
   }

   return true;
}

template <typename IntegerType, IntegerType diffValue>
bool Variable::Integer<IntegerType, diffValue>::decrement()
{
   if (minValue == variable)
   {
      if (!wrap)
         return false;
      else
         variable = maxValue;
   }
   else
   {
      if (variable < minValue + diffValue)
         variable = minValue;
      else
         variable -= diffValue;
   }

   return true;
}

// Enum

template <typename EnumType>
Variable::Enum<EnumType>::Enum(EnumType& variable, const Order& order, const bool wrap)
   : variable(variable)
   , order(order)
   , wrap(wrap)
{
}

template <typename EnumType>
bool Variable::Enum<EnumType>::change(bool up)
{
   if (up)
      return increment();
   else
      return decrement();
}

template <typename EnumType>
bool Variable::Enum<EnumType>::increment()
{
   if (order.empty())
      return false;

   if (order.back() == variable)
   {
      if (!wrap)
         return false;
      else
         variable = order.front();
   }
   else
   {
      const size_t index = getIndex() + 1;
      variable = order.at(index);
   }

   return true;
}

template <typename EnumType>
bool Variable::Enum<EnumType>::decrement()
{
   if (order.empty())
      return false;

   if (order.front() == variable)
   {
      if (!wrap)
         return false;
      else
         variable = order.back();
   }
   else
   {
      const size_t index = getIndex() - 1;
      variable = order.at(index);
   }

   return true;
}

template <typename EnumType>
size_t Variable::Enum<EnumType>::getIndex() const
{
   for (size_t index = 0; index < order.size(); index++)
   {
      if (order.at(index) == variable)
         return index;
   }

   return 0;
}

// other

uint16_t Variable::compileDigitCount(uint64_t number)
{
   uint16_t counter = 1;
   uint64_t test = 10;

   while (test < number)
   {
      counter++;
      test *= 10;
   }
   return counter;
}

#endif // VariableHPP
