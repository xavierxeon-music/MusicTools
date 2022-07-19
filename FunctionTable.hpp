#ifndef FunctionTableHPP
#define FunctionTableHPP

#include <Sound/FunctionTable.h>

FunctionTable::FunctionTable(AngleFunction angleFunction, const uint64_t& noOfSteps, const float maxAngle)
   : WaveTable::StepValueTable(noOfSteps, maxAngle)
{
   for (uint64_t index = 0; index < noOfSteps; index++)
   {
      const float angle = index * anglePerStep;
      const float value = angleFunction(angle);
      data[index] = value;
   }
}

#endif // FunctionTableHPP
