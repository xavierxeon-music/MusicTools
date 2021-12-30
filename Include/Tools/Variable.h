#ifndef VariableH
#define VariableH

#include <Global.h>

namespace Variable
{
   template <typename IntegerType, IntegerType diffValue = 1>
   class Integer
   {
   public:
      Integer(IntegerType& variable, const IntegerType& minValue, const IntegerType& maxValue, const bool wrap);

   public:
      bool change(bool up);
      bool increment();
      bool decrement();

   private:
      IntegerType& variable;
      const IntegerType minValue;
      const IntegerType maxValue;
      const bool wrap;
   };

   template <typename EnumType>
   class Enum
   {
   public:
      using Order = std::vector<EnumType>;

   public:
      Enum(EnumType& variable, const Order& order, const bool wrap);

   public:
      bool change(bool up);
      bool increment();
      bool decrement();

   private:
      size_t getIndex() const;

   private:
      EnumType& variable;
      const Order order;
      const bool wrap;
   };

} // namespace Variable

#include <Variable.hpp>

#endif // VariableH
