#ifndef WaveTableH
#define WaveTableH

#include <Abstract/AbstractOscilator.h>

#include <Maths.h>
#include <MusicTools.h>

namespace WaveTable
{
   class AbstractTable
   {
   public:
      inline AbstractTable(const float maxAngle = 2.0f * Maths::pi);

   public:
      inline const float& getMaxAngle() const;
      inline virtual float valueByAngle(const float& angle) const = 0;

   protected:
      const float maxAngle;
   };

   class StepTable : public AbstractTable
   {
   public:
      inline StepTable(uint64_t noOfSteps, const float maxAngle = 2.0f * Maths::pi);

   public:
      inline const uint64_t& getNoOfSteps() const;

   protected:
      inline uint64_t stepIndexFromAngle(float angle) const;

   protected:
      const uint64_t noOfSteps;
      const float anglePerStep;
   };

   // On Daisy device the frequency range is 2Hz to 20,000 Hz, otherwise any positive number.
   // A frequency of zero will turn off the oscilator.
   // Amplitude should be between 0 and 1.

   class Oscilator : public Abstract::Oscilator
   {
   public:
      inline Oscilator();

   public:
      inline void init(const AbstractTable* newTable, const float& newSampleRate);

      inline void setPhase(const float& newPhase);
      inline const float& getPhase() const;

      inline void setFrequency(const float& newFrequency);
      inline void setCycleDuration(const float& cylceDuration); // cylceDuration = 1.0 / frequency
      inline const float& getFrequency() const;

      inline void setAmplitude(const float& newAmplitude);
      inline const float& getAmplitude() const;

      inline float createSound() override;

   private:
      inline void compileDeltaPhase();

   private:
      const AbstractTable* table;
      float sampleRate;
      float phase;
      float frequency;
      float amplitude;
      float deltaPhase;
   };

} // namespace WaveTable

#ifndef WaveTableHPP
#include "../../WaveTable.hpp"
#endif // NOT WaveTableHPP

#endif // NOT WaveTableH
