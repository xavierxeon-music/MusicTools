#ifndef FunctionTableHPP
#define FunctionTableHPP

#include <Sound/FunctionTable.h>

FunctionTable::FunctionTable(AngleFunction angleFunction, uint64_t noOfSteps, const float maxAngle)
   : WaveTable::StepTable(noOfSteps, maxAngle)
   , table(nullptr)
{
   table = new float[noOfSteps];

   for (uint64_t index = 0; index < noOfSteps; index++)
   {
      const float angle = index * anglePerStep;
      const float value = angleFunction(angle);
      table[index] = value;
   }
}

float FunctionTable::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return table[index];
}

#endif // FunctionTableHPP
