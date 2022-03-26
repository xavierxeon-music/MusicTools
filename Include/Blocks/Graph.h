#ifndef GraphH
#define GraphH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

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
   inline void init();
   inline void clockTick();
   inline void clockReset();

   inline Tempo::Division getStepSize() const;
   inline void setStepSize(const Tempo::Division& newStepSize);
   inline void changeStepSize(bool longer);

   inline uint32_t getLength() const;
   // autoDiscard = true: stages exceeding new length will be removed
   // autoDiscard = false: if stages exceed new length, then length will not be changed
   inline LengthStatus setLength(const uint32_t newLength, bool autoDiscard = false);
   inline void trimLength(); // set length to fit stages

   inline uint8_t stageCount() const;
   // expandLength = true: adjust graph length to fit stages
   // expandLength = false: if new length exeeds current length, then do not add stage
   inline LengthStatus addStage(const uint8_t& atIndex, const uint8_t& startHeight, const uint8_t& stageLength, bool expandLength = true);
   inline void removeStage(const uint8_t& index);

   inline uint8_t getStageStartHeight(const uint8_t& index);
   inline void setStageStartHeight(const uint8_t& index, const uint8_t& startHeight);

   inline uint8_t getStageLength(const uint8_t& index);
   inline LengthStatus setStageLength(const uint8_t& index, const uint8_t& stageLength, bool expandLength = true);

   inline uint8_t getCurrentStageIndex() const;
   inline float getCurrentStagePercentage(const float& precentToNextTick = 0.0) const;
   inline float getCurrentValue(const float& precentToNextTick = 0.0) const;

   inline bool isLooping() const;
   inline void setLooping(bool on);

   inline bool isValid() const;

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

   using StepSize_ = Remember::Value<Tempo::Division>;
   using Length_ = Remember::Value<uint32_t>;
   using StageList_ = Remember::RefList<Stage>;
   using Loop_ = Remember::Value<bool>;

private:
   StepSize_ stepSize;
   Length_ length;
   StageList_ stages;
   Loop_ loop;

   uint64_t currentStageIndex;
   Counter stepSizeCounter;
   Counter stageLengthCounter;
   bool firstTickDone;
};

#ifndef GraphHPP
#include "../../Graph.hpp"
#endif // NOT GraphHPP

#endif // NOT GraphH
