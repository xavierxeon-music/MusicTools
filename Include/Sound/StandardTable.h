#ifndef StandardTableH
#define StandardTableH

#include <Sound/WaveTable.h>

struct Standard
{
   struct Waveform
   {
      enum Shape
      {
         Sine,
         Triange,
         Square,
         Saw,
         InvSaw
      };
      inline static std::string getName(const Shape& shape);
   };

   class Table : public WaveTable::StepValueTable<>
   {
   public:
      inline Table(const Waveform::Shape& waveform = Waveform::Sine);

   public:
      inline Waveform::Shape getWaveform() const;
      inline void setWaveform(const Waveform::Shape& newWaveform);

   private:
      inline void createStandardFrom();

   private:
      Waveform::Shape waveform;
   };
};

#ifndef StandardTableHPP
#include "../../StandardTable.hpp"
#endif // NOT StandardTableHPP

#endif // StandardTableH
