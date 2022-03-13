#ifndef GraphH
#define GraphH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

class Graph : public Remember::Container
{
public:
   class Stage : public Remember::Container
   {
   public:
      inline Stage(const uint8_t& startHeight = 0, const uint8_t& length = 0);
      inline virtual ~Stage();

   public:
      inline uint8_t getStartHeight() const;
      inline uint8_t getLength() const;

   private:
      friend class Graph;
      using StartHeight_ = Remember::Value<uint8_t>;
      using Length_ = Remember::Value<uint8_t>;

   private:
      StartHeight_ startHeight;
      Length_ length;
   };

public:
   inline Graph();

public:
   inline void init();
   inline void clockTick();
   inline void clockReset();

   inline Tempo::Division getStepSize() const;
   inline void setStepSize(const Tempo::Division& newStepSize);
   inline void changeStepSize(bool longer);

   inline uint8_t getLength() const;
   // autoDiscard = true: stages exceeding new length will be removed
   // autoDiscard = false: if stages exceed new length, then length will not be changed
   inline void setLength(const uint8_t newLength, bool autoDiscard = false);
   inline void trimLength(); // set length to fit stages

   inline uint8_t stageCount() const;
   inline Stage& getStage(const uint8_t& index);
   // expandLength = true: adjust graph length to fit stages
   // expandLength = false: if new length exeeds current length, then do not add stage
   inline void addStage(const uint8_t& startHeight, const uint8_t& stageLength, const uint8_t& atIndex, bool expandLength = true);
   inline void removeStage(const uint8_t& index);

   inline uint8_t getCurrentStageIndex() const;
   inline float getCurrentStagePercentage(const float& precentToNextTick = 0.0) const;
   inline float getCurrentValue(const float& precentToNextTick = 0.0) const;

   inline bool isValid() const;

private:
   using StepSize_ = Remember::Value<Tempo::Division>;
   using Length_ = Remember::Value<uint8_t>;
   using StageList_ = Remember::RefList<Stage>;

private:
   StepSize_ stepSize;
   Length_ length;
   StageList_ stages;

   uint64_t currentStageIndex;
   Counter stepSizeCounter;
   Counter stageLengthCounter;
   bool firstTickDone;
};

#include "Graph.hpp"

#endif // GraphH
