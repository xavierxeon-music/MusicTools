#ifndef StandardTableHPP
#define StandardTableHPP

#include <functional>

#include <Sound/StandardTable.h>

#include <Maths.h>

std::string Standard::Waveform::getName(const Shape& shape)
{
   if (Sine == shape)
      return "sin";
   else if (Triange == shape)
      return "tri";
   else if (Square == shape)
      return "sqr";
   else if (Saw == shape)
      return "saw";
   else if (InvSaw == shape)
      return "was";

   return "???";
}

// table

Standard::Table::Table()
   : WaveTable::StepValueTable()
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
   AngleFunction triangleFunction = [](const float& angle)
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
   AngleFunction sawFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = -1.0f + (2.0f * precent);

      return value;
   };

   // slope down
   AngleFunction invSawFunction = [](const float& angle)
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = 1.0f - (2.0f * precent);

      return value;
   };

   auto fillData = [&](AngleFunction angleFunction)
   {
      for (uint64_t index = 0; index < noOfSteps; index++)
      {
         const float angle = index * anglePerStep;         
         const float value = angleFunction(angle);
         data[index] = value;
         //std::cout << index << " " << value << std::endl;
      }
   };

   if (Waveform::Sine == newWaveform)
      fillData(sineFunction);
   else if (Waveform::Triange == newWaveform)
      fillData(triangleFunction);
   else if (Waveform::Square == newWaveform)
      fillData(sqaureFunction);
   else if (Waveform::Saw == newWaveform)
      fillData(sawFunction);
   else if (Waveform::InvSaw == newWaveform)
      fillData(invSawFunction);
}

#endif // StandardTableHPP
