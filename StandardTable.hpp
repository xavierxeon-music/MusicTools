#ifndef StandardTableHPP
#define StandardTableHPP

#include <functional>

#include <Sound/StandardTable.h>

#include <Maths.h>

std::string Standard::Waveform::getName(const Shape& shape)
{
   if (Sine == shape)
      return "sin";
   else if (Saw == shape)
      return "saw";
   else if (Square == shape)
      return "sqr";
   else if (SlopeUp == shape)
      return "up/";
   else if (SlopeDown == shape)
      return "dn\\";

   return "???";
}

// table

Standard::Table::Table()
   : WaveTable::StepTable(tableSize)
   , dataMap()
   , waveform(Waveform::Sine)
{
   using AngleFunction = std::function<float(const float& valuesPerAngle)>;

   auto fillData = [&](AngleFunction angleFunction, const Waveform::Shape& shape)
   {
      for (uint64_t index = 0; index < tableSize; index++)
      {
         const float angle = index * anglePerStep;
         const float value = angleFunction(angle);
         dataMap[shape][index] = value;
      }
   };

   // sine
   AngleFunction sineFunction = [](const float& angle)
   {
      return std::sin(angle);
   };
   fillData(sineFunction, Waveform::Sine);

   // saw
   AngleFunction sawFunction = [](const float& angle)
   {
      if (angle <= Maths::pi)
      {
         const float precent = angle / Maths::pi;
         const float value = -1.0f + (2.0f * precent);

         return value;
      }
      else
      {
         const float precent = (angle - Maths::pi) / Maths::pi;
         const float value = 1.0f - (2.0f * precent);

         return value;
      }
   };
   fillData(sawFunction, Waveform::Saw);

   // square
   AngleFunction sqaureFunction = [](const float& angle)
   {
      if (angle <= Maths::pi)
         return 1.0f;
      else
         return -1.0f;
   };
   fillData(sqaureFunction, Waveform::Square);

   // slope up
   AngleFunction slopeUpFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = -1.0f + (2.0f * precent);

      return value;
   };
   fillData(slopeUpFunction, Waveform::SlopeUp);

   // slope down
   AngleFunction slopeDownFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = 1.0f - (2.0f * precent);

      return value;
   };
   fillData(slopeDownFunction, Waveform::SlopeDown);
}

void Standard::Table::setWaveform(const Waveform::Shape& newWaveform)
{
   waveform = newWaveform;
}

float Standard::Table::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return dataMap.at(waveform)[index];
}

#endif // StandardTableHPP
