#ifndef StandardTableH
#define StandardTableH

#include <map>
#include <string>

#include <Sound/WaveTable.h>

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
      inline static std::string getName(const Shape& shape);
   };

   class Table : public WaveTable::StepValueTable
   {
   public:
      inline Table();

   public:
      inline void setWaveform(const Waveform::Shape& newWaveform);
   };
};

#ifndef StandardTableHPP
#include "../../StandardTable.hpp"
#endif // NOT StandardTableHPP

#endif // StandardTableH
