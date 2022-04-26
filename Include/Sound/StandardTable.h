#ifndef StandardTableH
#define StandardTableH

#include <string>

#include <Sound/FunctionTable.h>

struct Standard
{
   struct Waveform
   {
      enum Shape
      {
         Sine,
         Saw,
         Square,
         SlopeUp,
         SlopeDown
         // TODO noise
      };
   };

   inline static std::string getName(const Waveform::Shape& shape);
   inline static const WaveTable::Table* getTable(const Waveform::Shape& shape);
   static constexpr uint64_t tableSize = 4096; // TODO try smaller size
};

#ifndef StandardTableHPP
#include "../../StandardTable.hpp"
#endif // NOT StandardTableHPP

#endif // StandardTableH
