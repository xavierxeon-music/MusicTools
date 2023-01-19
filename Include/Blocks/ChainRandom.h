#ifndef ChainRandomH
#define ChainRandomH

#include <Abstract/AbstractChain.h>
#include <Remember.h>

#include <Tools/FastRandom.h>
#include <Tools/Range.h>

class ChainRandom : public Abstract::Chain, public Remember::Container
{
public:
   enum class Type
   {
      Ramp,   // glide from start value to end value
      Steady, // start value == end value
      RndGate // radndom gate (force value to be either 0 or 255)
   };

public:
   inline ChainRandom();

public:
   inline uint8_t getValue(const float& tickPercentage) const;
   inline bool isOn() const;
   inline const Tempo::Tick& getCurrentBarDuration() const;
   inline uint8_t linkStartValue() const;
   inline uint8_t linkEndValue() const;

   inline const Type& getType() const;
   inline void setType(const Type& newType);

   inline const uint8_t& getMinValue() const;
   inline bool setMinValue(const uint8_t& newValue);

   inline const uint8_t& getMaxValue() const;
   inline bool setMaxValue(const uint8_t& newValue);

   inline const Tempo::Tick& getMinBarDuration() const;
   inline bool setMinBarDuration(const Tempo::Tick& newDuration);

   inline const Tempo::Tick& getMaxBarDuration() const;
   inline bool setMaxBarDuration(const Tempo::Tick& newDuration);

private:
   struct Link : public Abstract::Chain::Link
   {
      uint8_t startValue;
      uint8_t endValue;
   };

   using Type_ = Remember::Value<Type>;
   using Value_ = Remember::Value<uint8_t>;
   using Duration_ = Remember::Value<Tempo::Tick>;

private:
   inline void postRead() override;
   inline void linkDone(Abstract::Chain::Link* link) override;
   inline void rollDice();

private:
   Link link;
   Tempo::Tick currentBarDuration;
   FastRandom generator;
   Type_ type;

   Value_ minValue;
   Value_ maxValue;
   Range::Mapper valueMapper;

   Duration_ minBarDuration;
   Duration_ maxBarDuration;
   Range::Mapper durationMapper;
};

#ifndef ChainRandomHPP
#include "../../ChainRandom.hpp"
#endif // NOT ChainRandomHPP

#endif // NOT ChainRandomH
