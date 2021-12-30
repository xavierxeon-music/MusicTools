#ifndef FunctionTableHPP
#define FunctionTableHPP

#include <Sound/FunctionTable.h>

FunctionTable::FunctionTable(uint64_t resolution, const float maxAngle)
   : CircularTable(maxAngle)
   , resolution(resolution)
   , anglePerStep(maxAngle / static_cast<float>(resolution))
   , table(nullptr)
{
   table = new float[resolution];
}

FunctionTable::FunctionTable(uint64_t resolution, AngleFunction angleFunction, const float maxAngle)
   : FunctionTable(resolution, maxAngle)
{
   for (uint64_t index = 0; index < resolution; index++)
   {
      const float angle = index * anglePerStep;
      const float value = angleFunction(angle);
      table[index] = value;
   }
}

float FunctionTable::valueByAngle(const float& angle) const
{
   const uint64_t index = getIndexFromAngle(angle);
   return table[index];
}

const uint64_t& FunctionTable::getResolution() const
{
   return resolution;
}

uint64_t FunctionTable::getIndexFromAngle(float angle) const
{
   while (angle < 0)
      angle += maxAngle;

   while (angle >= maxAngle)
      angle -= maxAngle;

   const uint64_t index = static_cast<uint64_t>(angle / anglePerStep);
   return index;
}


#endif // FunctionTableHPP
