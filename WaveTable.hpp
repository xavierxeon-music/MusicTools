#ifndef WaveTableHPP
#define WaveTableHPP

#include <Sound/WaveTable.h>

// table

WaveTable::AbstractTable::AbstractTable(const float maxAngle)
   : maxAngle(maxAngle)
{
}

WaveTable::AbstractTable::~AbstractTable()
{
}

const float& WaveTable::AbstractTable::getMaxAngle() const
{
   return maxAngle;
}

// step table

WaveTable::StepTable::StepTable(const uint64_t& noOfSteps, const float& maxAngle)
   : AbstractTable(maxAngle)
   , noOfSteps(noOfSteps)
   , anglePerStep(maxAngle / static_cast<float>(noOfSteps))
{
}

WaveTable::StepTable::~StepTable()
{
}

const uint64_t& WaveTable::StepTable::getNoOfSteps() const
{
   return noOfSteps;
}

uint64_t WaveTable::StepTable::stepIndexFromAngle(float angle) const
{
   while (angle < 0)
      angle += maxAngle;

   while (angle >= maxAngle)
      angle -= maxAngle;

   const uint64_t index = static_cast<uint64_t>(angle / anglePerStep);
   return index;
}

// step value table

template <uint64_t TableSize>
WaveTable::StepValueTable<TableSize>::StepValueTable(const float& maxAngle)
   : StepTable(TableSize, maxAngle)
   , data{}
{
   for (uint64_t index = 0; index < TableSize; index++)
      data[index] = 0.0;
}

template <uint64_t TableSize>
float WaveTable::StepValueTable<TableSize>::valueByIndex(const uint64_t index) const
{
   return data[index];
}

template <uint64_t TableSize>
float WaveTable::StepValueTable<TableSize>::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return valueByIndex(index);
}

#endif // NOT WaveTableHPP
