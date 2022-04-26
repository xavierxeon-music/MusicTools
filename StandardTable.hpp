#ifndef StandardTableHPP
#define StandardTableHPP

#include <Sound/StandardTable.h>

#include <Maths.h>

std::string Standard::getName(const Waveform::Shape& shape)
{
   if (Standard::Waveform::Sine == shape)
      return "sin";
   else if (Standard::Waveform::Saw == shape)
      return "saw";
   else if (Standard::Waveform::Square == shape)
      return "sqr";
   else if (Standard::Waveform::SlopeUp == shape)
      return "up/";
   else if (Standard::Waveform::SlopeDown == shape)
      return "dn\\";

   return "???";
}

const WaveTable::Table* Standard::getTable(const Waveform::Shape& shape)
{
   // sine
   auto sineFunction = [](const float& angle) -> float
   {
      return std::sin(angle);
   };
   static const FunctionTable sineTable(Standard::tableSize, sineFunction);

   // saw
   auto sawFunction = [](const float& angle) -> float
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
   static const FunctionTable sawTable(tableSize, sawFunction);

   // square
   auto sqaureFunction = [](const float& angle) -> float
   {
      static const float pi = 0.5f * 2.0f * Maths::pi;
      if (angle <= pi)
         return 1.0f;
      else
         return -1.0f;
   };
   static const FunctionTable sqaureTable(tableSize, sqaureFunction);

   // slope up
   auto slopeUpFunction = [](const float& angle) -> float
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = -1.0f + (2.0f * precent);

      return value;
   };
   static const FunctionTable slopeUpTable(tableSize, slopeUpFunction);

   // slope down
   auto slopeDownFunction = [](const float& angle) -> float
   {
      const float precent = angle / (2.0f * Maths::pi);
      const float value = 1.0f - (2.0f * precent);

      return value;
   };
   static const FunctionTable slopeDownTable(tableSize, slopeDownFunction);

   //
   if (Standard::Waveform::Sine == shape)
      return &sineTable;
   else if (Standard::Waveform::Saw == shape)
      return &sawTable;
   else if (Standard::Waveform::Square == shape)
      return &sqaureTable;
   else if (Standard::Waveform::SlopeUp == shape)
      return &slopeUpTable;
   else if (Standard::Waveform::SlopeDown == shape)
      return &slopeDownTable;

   return nullptr;
}

#endif // StandardTableHPP
