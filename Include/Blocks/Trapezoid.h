#ifndef TrapezoidH
#define TrapezoidH

#include <Storage/Remember.h>

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
   inline static std::string stageName();

   inline void init();
   inline void clockTick();
   inline void clockReset();

   inline const Stage& getCurrentStage() const;
   inline const uint8_t& getLength(const Stage& stage) const;
   inline void changeLength(const Stage& stage, bool longer);

   inline float getCurrentStagePercentage() const;
   inline float getCurrentValues() const;

   inline const Tempo::Division& getStepSize() const;
   inline void changeStepSize(bool longer);

   inline float getBound(const Bound& bound) const;
   inline void changeBound(const Bound& bound, bool more);

   inline bool isValid() const;

private: // things to remeber
   using StageValues_ = Remember::ValueArray<uint8_t, 5>;
   using BoundValues_ = Remember::ValueArray<float, 2>;
   using StepSize_ = Remember::Value<Tempo::Division>;

private:
   uint32_t getStageDuration() const;
   void advanceToNextStage();
   void setIndexCounterLength();

private:
   StageValues_ stages;
   BoundValues_ bounds;
   StepSize_ stepSize;

   Stage stage;
   Counter stepCounter;
   Counter indexCounter;
   bool firstTick;
};

#include "Trapezoid.hpp"

#endif // TrapezoidH
