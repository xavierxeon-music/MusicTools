#ifndef WaveTableMorpherHPP
#define WaveTableMorpherHPP

#include <Sound/WaveTableMorpher.h>

WaveTable::Morpher::Morpher()
   : AbstractTable()
   //, dataList()
   , mixStep(0)
   , mix(0.0)
   , loop(false)
{
}

void WaveTable::Morpher::addTable(AbstractTable* table, const uint64_t& maxSteps)
{
   Data data{table, maxSteps};
   dataList.push_back(data);
}

bool WaveTable::Morpher::step()
{
   if (dataList.empty())
      return false;

   const uint64_t& maxSteps = dataList.at(0).maxSteps;
   if (0 == maxSteps)
      return false;

   mixStep++;
   if (maxSteps <= mixStep)
   {
      mix = 0.0;
      mixStep = 0;
      swap();
      return true;
   }
   else
   {
      mix = mixStep / maxSteps;
   }

   return false;
}

void WaveTable::Morpher::setMix(const float newMix)
{
   mix = newMix;
}

const float& WaveTable::Morpher::getMix() const
{
   return mix;
}

void WaveTable::Morpher::setLoop(bool enabled)
{
   loop = enabled;
}

void WaveTable::Morpher::swap()
{
}

float WaveTable::Morpher::valueByAngle(const float& angle) const
{
   if (dataList.empty())
      return 0.0;

   const AbstractTable* firstTable = dataList.at(0).table;
   const float firstValue = firstTable->valueByAngle(angle);
   if (1 == dataList.size())
      return firstValue;

   const AbstractTable* secondTable = dataList.at(1).table;
   const float secondValue = secondTable->valueByAngle(angle);

   const float value = ((1.0 - mix) * firstValue) + (mix * secondValue);
   return value;
}

#endif // NOT TableMorpherHPP
