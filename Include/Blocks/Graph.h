#ifndef GraphH
#define GraphH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

// a stage liinearly changes its value during its length from its start height to the start height of the next stage
// the length of the last stage is ignored.
//  * instead the remaining length in the graph is used.
//  * the end value is the start height of the first stage
// if anythong but the height of a stage is edited the graph will be reset
// if the graph is not looping the value will always be zero after the last stage

// CALL clockReset AFTER LOAD!

class Graph : public Remember::Container
{
public:
   enum class LengthStatus
   {
      Kept,
      Changed,
      Error,
   };

public:
   inline Graph();

public:
   inline void clockTick();
   inline void clockReset();

   inline uint8_t getCurrentStageIndex() const;
   inline float getCurrentStagePercentage(const float& precentToNextTick = 0.0) const;
   inline float getCurrentValue(const float& precentToNextTick = 0.0) const;

   inline bool isValid() const;

   inline Tempo::Division getStepSize() const;
   inline void setStepSize(const Tempo::Division& newStepSize);
   inline void changeStepSize(bool longer);

   inline uint32_t getLength() const;
   // autoDiscard = true: stages exceeding new length will be removed
   // autoDiscard = false: if stages exceed new length, then length will not be changed
   inline LengthStatus setLength(const uint32_t newLength, bool autoDiscard = false);
   inline void trimLength(); // set length to fit stages

   inline uint8_t stageCount() const;
   inline LengthStatus addStage(const uint8_t& afterIndex, const uint32_t& numberOfStages = 1);
   inline void moveStage(const uint8_t& fromIndex, const uint8_t& toIndex);
   inline void removeStage(const uint8_t& index);

   inline uint8_t getStageStartHeight(const uint8_t& index);
   inline void setStageStartHeight(const uint8_t& index, const uint8_t& startHeight);

   inline uint8_t getStageLength(const uint8_t& index);
   // expandLength = true: adjust graph length to fit stages
   // expandLength = false: if new length exeeds current length, then do not add stage
   inline LengthStatus setStageLength(const uint8_t& index, const uint8_t& stageLength, bool expandLength = true);
   inline LengthStatus setStageStartHeigthAndLength(const uint8_t& index, const uint8_t& startHeight, const uint8_t& stageLength, bool expandLength = true);

   inline bool isLooping() const;
   inline void setLooping(bool on);


private:
   class Stage : public Remember::Container
   {
   public:
      inline Stage(const uint8_t& startHeigh = 255, const uint8_t& stageLength = 0);
      inline Stage(const Stage& other);
      inline virtual ~Stage();

      inline Stage& operator=(const Stage& other);

   private:
      friend class Graph;
      using StartHeight_ = Remember::Value<uint8_t>;
      using StageLength_ = Remember::Value<uint8_t>;

   private:
      StartHeight_ startHeight;
      StageLength_ stageLength;
   };

private:
   inline uint32_t compileStageLength(const uint8_t& index) const;

private:
   using StepSize_ = Remember::Value<Tempo::Division>;
   using Length_ = Remember::Value<uint32_t>;
   using StageList_ = Remember::RefList<Stage>;
   using Loop_ = Remember::Value<bool>;

private:
   StepSize_ stepSize;
   Length_ graphLength;
   StageList_ stages;
   Loop_ loop;
   bool pastLoop;

   uint64_t currentStageIndex;
   Counter stepSizeCounter;
   uint32_t stepsTaken;
   Counter stageLengthCounter;
   bool firstTickDone;
};

#ifndef GraphHPP
#include "../../Graph.hpp"
#endif // NOT GraphHPP

#endif // NOT GraphH
