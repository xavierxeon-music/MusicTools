#ifndef WaveTableOscilatorH
#define WaveTableOscilatorH

#include <Abstract/AbstractOscilator.h>

namespace WaveTable
{
   class AbstractTable;

   // On Daisy device the frequency range is 2Hz to 20,000 Hz, otherwise any positive number.
   // A frequency of zero will turn off the oscilator.
   // Amplitude should be between 0 and 1.

   class Oscilator : public Abstract::Oscilator
   {
   public:
      inline Oscilator();

   public:
      inline void init(const AbstractTable* newTable, const float& newSampleRate);

      inline void reset();
      inline void setPhase(const float& newPhase); // -1 to +1, corresponds to -2pi to +2pi
      inline const float& getPhase() const;

      inline bool setFrequency(const float& newFrequency) override;
      inline float createSound() override;

   private:
      inline void normalizeAngle(float& value);
      inline void compileDeltaAngle();

   private:
      const AbstractTable* table;
      float sampleRate;
      float phase;      // user defined angle offset
      float angle;      // current angle without phase
      float deltaAngle; // offset to the next angle, depends on frequency
   };

} // namespace WaveTable

#ifndef WaveTableOscilatorHPP
#include "../../WaveTableOscilator.hpp"
#endif // NOT WaveTableOscilatorHPP

#endif // NOT WaveTableOscilatorH
