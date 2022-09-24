#ifndef WaveTableH
#define WaveTableH

#include <Maths.h>
#include <MusicTools.h>

namespace WaveTable
{
   class AbstractTable
   {
   public:
      inline AbstractTable(const float maxAngle = 2.0f * Maths::pi);
      inline virtual ~AbstractTable();

   public:
      inline const float& getMaxAngle() const;
      inline virtual float valueByAngle(const float& angle) const = 0;

   protected:
      const float maxAngle;
   };

   class StepTable : public AbstractTable
   {
   public:
      inline StepTable(const uint64_t& noOfSteps, const float& maxAngle = 2.0f * Maths::pi);
      inline virtual ~StepTable();

   public:
      inline const uint64_t& getNoOfSteps() const;

   protected:
      inline uint64_t stepIndexFromAngle(float angle) const;

   protected:
      const uint64_t noOfSteps;
      const float anglePerStep;
   };

   class StepValueTable : public StepTable
   {
   public:
      inline StepValueTable(const uint64_t tableSize = 1024, const float& maxAngle = 2.0f * Maths::pi);
      inline ~StepValueTable();

   public:
      inline float valueByIndex(const uint64_t index) const;
      inline virtual float valueByAngle(const float& angle) const override;

   protected:
      float* data;
   };

} // namespace WaveTable

#ifndef WaveTableHPP
#include "../../WaveTable.hpp"
#endif // NOT WaveTableHPP

#endif // NOT WaveTableH
