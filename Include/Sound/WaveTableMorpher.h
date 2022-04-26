#ifndef WaveTableMorpherH
#define WaveTableMorpherH

#include <Sound/WaveTable.h>

namespace WaveTable
{
   // zero tables = no sound
   // one table = no morph, no step, no mix, no swap
   // step and morph work between first and second table only
   class Morpher : public Table
   {
   public:
      inline Morpher();

   public:
      inline void addTable(const Table* table, const uint64_t& maxSteps = 0);
      inline virtual bool step();             // advance mix. if at end (i.e. mix == 1.0) call swap and return true
      inline void setMix(const float newMix); // override mix. do not use with step or else odd behaviour. does not call swap!
      inline const float& getMix() const;     // get current mix
      inline void setLoop(bool enabled);      // see swap
      inline void swap();                     // removes first table. if loop is set the table will be appended to the end of the list
      inline float valueByAngle(const float& angle) const override final;

   private:
      struct Data
      {
         const Table* table;
         const uint64_t maxSteps;

         using List = std::vector<Data>;
      };

   private:
      Data::List dataList;
      uint64_t mixStep; // zero to duration of current data
      float mix;
      bool loop;
   };
} // namespace WaveTable

#ifndef WaveTableMorpherHPP
#include "../../WaveTableMorpher.hpp"
#endif // NOT WaveTableMorpherHPP

#endif // NOT WaveTableMorpherH
