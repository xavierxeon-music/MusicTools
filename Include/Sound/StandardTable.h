#ifndef StandardTableH
#define StandardTableH

#include <Sound/WaveTable.h>

#include <Tools/FastRandom.h>

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
         InvSaw,
         Noise
      };
      inline static std::string getName(const Shape& shape);
   };

   class Table : public WaveTable::StepValueTable
   {
   public:
      inline Table(const Waveform::Shape& waveform = Waveform::Sine);

   public:
      inline Waveform::Shape getWaveform() const;
      inline void setWaveform(const Waveform::Shape& newWaveform);

      inline float valueByIndex(const uint64_t index) const override;

   private:
      inline void createStandardFrom();

   private:
      Waveform::Shape waveform;
      mutable FastRandom noise;
   };
};

#ifndef StandardTableHPP
#include "../../StandardTable.hpp"
#endif // NOT StandardTableHPP

#endif // StandardTableH
