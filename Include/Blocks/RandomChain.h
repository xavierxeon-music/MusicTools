#ifndef RandomChainH
#define RandomChainH

#include <Abstract/AbstractChain.h>

#include <Tools/FastRandom.h>
#include <Tools/Range.h>

class RandomChain : public Abstract::Chain
{
public:
   enum class Type
   {
      Ramp,   // glide from start value to end value
      Steady, // start value == end value
      Gate    // ignore min and max values, either 0 or 255
   };

public:
   inline RandomChain(const Type& type);

public:
   uint8_t getValue(const float& tickPercentage);

   const uint8_t& getMinValue() const;
   void setMinValue(const uint8_t& newValue);

   const uint8_t& getMaxValue() const;
   void setMaxValue(const uint8_t& newValue);

   const Tempo::Tick& getMinDuration() const;
   void setMinDuration(const Tempo::Tick& newDuration);

   const Tempo::Tick& getMaxDuration() const;
   void setMaxDuration(const Tempo::Tick& newDuration);

private:
   class Link : public Abstract::Chain::Link
   {
   private:
      friend class RandomChain;

   private:
      uint8_t startValue;
      uint8_t endValue;
   };

private:
   void linkDone(Abstract::Chain::Link* link) override;
   void rollDice();

private:
   const Type type;
   uint8_t minValue;
   uint8_t maxValue;
   Tempo::Tick minDuration;
   Tempo::Tick maxDuration;

   Link link;
   Range::Mapper valueMapper;
   Range::Mapper durationMapper;
   static FastRandom generator;
};

#ifndef RandomChainHPP
#include "../../RandomChain.hpp"
#endif // NOT RandomChainHPP

#endif // NOT RandomChainH
