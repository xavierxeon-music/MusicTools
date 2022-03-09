#ifndef TrapezoidH
#define TrapezoidH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

class Trapezoid : public Remember::Container
{
public:
   enum class Stage
   {
      Wait,
      Rise,
      High,
      Fall,
      Low
   };

   enum class Bound
   {
      Min,
      Max
   };

public:
   inline Trapezoid();

public:
   inline static std::string stageName(const Stage& stage);

   inline void init();
   inline void clockTick();
   inline void clockReset();

   inline const Stage& getCurrentStage() const;
   inline float getCurrentStagePercentage(const float& precentToNextTick = 0.0) const;
   inline float getCurrentValue(const float& precentToNextTick = 0.0) const;

   inline const uint8_t& getStageLength(const Stage& stage) const;
   inline void changeStageLength(const Stage& stage, bool longer);

   inline Tempo::Division getStepSize() const;
   inline void changeStepSize(bool longer);

   inline float getBound(const Bound& bound) const;
   inline void changeBound(const Bound& bound, bool more);

   inline bool isValid() const;

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

#include "Trapezoid.hpp"

#endif // TrapezoidH
