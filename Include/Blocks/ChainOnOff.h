#ifndef ChainOnOffH
#define ChainOnOffH

#include <Abstract/AbstractChain.h>
#include <Remember.h>

#include <Tools/FastRandom.h>
#include <Tools/Range.h>

class ChainOnOff : public Abstract::Chain, public Remember::Container
{
public:
   inline ChainOnOff();

public:
   inline bool isOn() const;
   inline const Tempo::Tick& getCurrentBarDuration() const;

   inline bool getInitialOn() const;
   inline void setInitialOn(bool on);

   inline const Tempo::Tick& getMinBarDurationOn() const;
   inline bool setMinBarDurationOn(const Tempo::Tick& value);

   inline const Tempo::Tick& getMaxBarDurationOn() const;
   inline bool setMaxBarDurationOn(const Tempo::Tick& value);

   inline const Tempo::Tick& getMinBarDurationOff() const;
   inline bool setMinBarDurationOff(const Tempo::Tick& value);

   inline const Tempo::Tick& getMaxBarDurationOff() const;
   inline bool setMaxBarDurationOff(const Tempo::Tick& value);

private:
   struct Link : public Abstract::Chain::Link
   {
      bool on;
   };

   using On_ = Remember::Value<bool>;
   using Duration_ = Remember::Value<Tempo::Tick>;

private:
   inline void postRead() override;
   inline void linkDone(Abstract::Chain::Link* link) override;
   inline void rollDice();

private:
   Link link;
   On_ initialOn;
   Tempo::Tick currentBarDuration;
   FastRandom generator;

   Duration_ minBarDurationOn;
   Duration_ maxBarDurationOn;
   Range::Mapper durationMapperOn;

   Duration_ minBarDurationOff;
   Duration_ maxBarDurationOff;
   Range::Mapper durationMapperOff;
};

#ifndef ChainOnOffHPP
#include "./../ChainOnOff.hpp"
#endif // NOT ChainOnOffHPP

#endif // NOT ChainOnOffH
