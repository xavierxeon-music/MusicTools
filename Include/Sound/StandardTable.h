#ifndef StandardTableH
#define StandardTableH

#include <map>
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
      inline static std::string getName(const Shape& shape);
   };

   class Table : public WaveTable::Table
   {
   public:
      inline Table();

   public:
      inline void setWaveform(const Waveform::Shape& newWaveform);
      inline virtual float valueByAngle(const float& angle) const override;
      inline const uint64_t& getResolution() const;

   private:
      static constexpr uint64_t tableSize = 4096;
      using Data = float[tableSize];
      using DataMap = std::map<Waveform::Shape, Data>;

   private:
      DataMap dataMap;
      Waveform::Shape waveform;
      const float anglePerStep;
   };
};

#ifndef StandardTableHPP
#include "../../StandardTable.hpp"
#endif // NOT StandardTableHPP

#endif // StandardTableH
