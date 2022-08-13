#ifndef TrapezoidH
#define TrapezoidH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

pyexport class Trapezoid : public Remember::Container
{
public:
   pyexport enum class Stage //
   {
      Wait,
      Rise,
      High,
      Fall,
      Low
   };

   pyexport enum class Bound //
   {
      Min,
      Max
   };

public:
   pyexport inline Trapezoid();

public:
   pyexport inline static std::string stageName(const Stage& stage);

   pyexport inline void init();
   pyexport inline void clockTick();
   pyexport inline void clockReset();

   pyexport inline const Stage& getCurrentStage() const;
   pyexport inline float getCurrentStagePercentage(const float& precentToNextTick = 0.0) const;
   pyexport inline float getCurrentValue(const float& precentToNextTick = 0.0) const;

   pyexport inline const uint8_t& getStageLength(const Stage& stage) const;
   pyexport inline void setStageLength(const Stage& stage, const uint8_t& newLength);
   pyexport inline void changeStageLength(const Stage& stage, bool longer);

   pyexport inline Tempo::Division getStepSize() const;
   pyexport inline void setStepSize(const Tempo::Division& newStepSize);
   pyexport inline void changeStepSize(bool longer);

   pyexport inline float getBound(const Bound& bound) const;
   pyexport inline void setBound(const Bound& bound, const float& newValue);
   pyexport inline void changeBound(const Bound& bound, bool more);

   pyexport inline bool isValid() const;

private: // things to remeber
   using StageValues_ = Remember::ValueArray<uint8_t, 5>;
   using BoundValues_ = Remember::ValueArray<uint8_t, 2>;
   using StepSize_ = Remember::Value<Tempo::Division>;

private:
   inline uint32_t getStageDuration() const;
   inline void advanceToNextStage();
   inline void setStageLengthCounterMaxValue();

private:
   StageValues_ stages;
   BoundValues_ bounds;
   StepSize_ stepSize;

   Stage stage;
   Counter stepSizeCounter;
   Counter stageLengthCounter;
   bool firstTickDone;
};

#ifndef TrapezoidHPP
#include "../../Trapezoid.hpp"
#endif // NOT TrapezoidHPP

#endif // NOT TrapezoidH
