#ifndef VariableH
#define VariableH

#include <MusicTools.h>

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

   inline static uint16_t compileDigitCount(uint64_t number);

} // namespace Variable

#ifndef VariableHPP
#include "../../Variable.hpp"
#endif // NOT VariableHPP

#endif // NOT VariableH
