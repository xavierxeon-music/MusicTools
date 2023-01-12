#ifndef RandomChainH
#define RandomChainH

#include <Abstract/AbstractChain.h>
#include <Remember.h>

#include <Tools/FastRandom.h>
#include <Tools/Range.h>

class RandomChain : public Abstract::Chain, public Remember::Container
{
public:
   enum class Type
   {
      Ramp,   // glide from start value to end value
      Steady, // start value == end value
      Gate    // ignore min and max values, either 0 or 255
   };

public:
   inline RandomChain();

public:
   inline uint8_t getValue(const float& tickPercentage) const;
   inline bool isOn() const;

   inline const Type& getType() const;
   inline void setType(const Type& newType);

   inline const uint8_t& getMinValue() const;
   inline void setMinValue(const uint8_t& newValue);

   inline const uint8_t& getMaxValue() const;
   inline void setMaxValue(const uint8_t& newValue);

   inline const Tempo::Tick& getMinBarDuration() const;
   inline void setMinBarDuration(const Tempo::Tick& newDuration);

   inline const Tempo::Tick& getMaxBarDuration() const;
   inline void setMaxBarDuration(const Tempo::Tick& newDuration);

   inline const Tempo::Tick& getCurrentBarDuration() const;

private:
   class Link : public Abstract::Chain::Link
   {
   private:
      friend class RandomChain;

   private:
      uint8_t startValue;
      uint8_t endValue;
   };

   using Type_ = Remember::Value<Type>;
   using Value_ = Remember::Value<uint8_t>;
   using Duration_ = Remember::Value<Tempo::Tick>;

private:
   inline void linkDone(Abstract::Chain::Link* link) override;
   inline void rollDice();

private:
   Type_ type;
   Value_ minValue;
   Value_ maxValue;
   Duration_ minBarDuration;
   Duration_ maxBarDuration;

   Link link;
   Range::Mapper valueMapper;
   Range::Mapper durationMapper;
   Tempo::Tick currentBarDuration;
   FastRandom generator;
};

#ifndef RandomChainHPP
#include "../../RandomChain.hpp"
#endif // NOT RandomChainHPP

#endif // NOT RandomChainH
