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
   , data{}
{
   setWaveform(Waveform::Sine);
}

void Standard::Table::setWaveform(const Waveform::Shape& newWaveform)
{
   using AngleFunction = std::function<float(const float& valuesPerAngle)>;

   // sine
   AngleFunction sineFunction = [](const float& angle)
   {
      return std::sin(angle);
   };

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

   // square
   AngleFunction sqaureFunction = [](const float& angle)
   {
      if (angle <= Maths::pi)
         return 1.0f;
      else
         return -1.0f;
   };

   // slope up
   AngleFunction slopeUpFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = -1.0f + (2.0f * precent);

      return value;
   };

   // slope down
   AngleFunction slopeDownFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = 1.0f - (2.0f * precent);

      return value;
   };

   auto fillData = [&](AngleFunction angleFunction)
   {
      for (uint64_t index = 0; index < tableSize; index++)
      {
         const float angle = index * anglePerStep;
         const float value = angleFunction(angle);
         data[index] = value;
      }
   };

   if (Waveform::Sine == newWaveform)
      fillData(sineFunction);
   else if (Waveform::Saw == newWaveform)
      fillData(sawFunction);
   else if (Waveform::Square == newWaveform)
      fillData(sqaureFunction);
   else if (Waveform::SlopeUp == newWaveform)
      fillData(slopeUpFunction);
   else if (Waveform::SlopeDown == newWaveform)
      fillData(slopeDownFunction);
}

float Standard::Table::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return data[index];
}

#endif // StandardTableHPP
