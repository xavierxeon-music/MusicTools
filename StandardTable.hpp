#ifndef StandardTableHPP
#define StandardTableHPP

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
   : WaveTable::Table()
   , dataMap()
   , waveform(Waveform::Sine)
   , anglePerStep(maxAngle / static_cast<float>(tableSize))
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
   AngleFunction sawFunction = [](const float& angle) -> float
   {
      static const float pi = 0.5 * 2.0f * Maths::pi;
      if (angle <= pi)
      {
         const float precent = angle / pi;
         const float value = -1.0f + (2.0f * precent);

         return value;
      }
      else
      {
         const float precent = (angle - pi) / pi;
         const float value = 1.0f - (2.0f * precent);

         return value;
      }
   };
   fillData(sawFunction, Waveform::Saw);

   // square
   AngleFunction sqaureFunction = [](const float& angle) -> float
   {
      static const float pi = 0.5f * 2.0f * Maths::pi;
      if (angle <= pi)
         return 1.0f;
      else
         return -1.0f;
   };
   fillData(sqaureFunction, Waveform::Square);

   // slope up
   AngleFunction slopeUpFunction = [](const float& angle) -> float
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = -1.0f + (2.0f * precent);

      return value;
   };
   fillData(slopeUpFunction, Waveform::SlopeUp);

   // slope down
   AngleFunction slopeDownFunction = [](const float& angle) -> float
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
   auto getIndexFromAngle = [&](float angle) -> uint64_t
   {
      while (angle < 0)
         angle += maxAngle;

      while (angle >= maxAngle)
         angle -= maxAngle;

      const uint64_t index = static_cast<uint64_t>(angle / anglePerStep);
      return index;
   };

   const uint64_t index = getIndexFromAngle(angle);
   return dataMap.at(waveform)[index];
}

const uint64_t& Standard::Table::getResolution() const
{
   return tableSize;
}

#endif // StandardTableHPP
