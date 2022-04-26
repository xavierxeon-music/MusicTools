#ifndef WaveTableH
#define WaveTableH

#include <Abstract/AbstractOscilator.h>

#include <Maths.h>
#include <MusicTools.h>

namespace WaveTable
{
   class Table
   {
   public:
      inline Table(const float maxAngle = 2.0f * Maths::pi);
      inline virtual ~Table();

   public:
      inline const float& getMaxAngle() const;
      inline virtual float valueByAngle(const float& angle) const = 0;

   protected:
      const float maxAngle;
   };

   // On Daisy device the frequency range is 2Hz to 20,000 Hz, otherwise any positive number
   // A frequency of zero will turn off the oscilaotr.
   // Amplitude should be between 0 and 1.

   class Oscilator : public Abstract::Oscilator
   {
   public:
      inline Oscilator();

   public:
      inline void init(const Table* newTable, const float& newSampleRate);

      inline void setPhase(const float& newPhase);
      inline const float& getPhase() const;

      inline void setFrequency(const float& newFrequency);
      inline void setCycleDuration(const float& cylceDuration);
      inline const float& getFrequency() const;

      inline void setAmplitude(const float& newAmplitude);
      inline const float& getAmplitude() const;

      inline float createSound() override;
      inline static float frequencyFromCV(float voltage);

   private:
      inline void compileDeltaPhase();

   private:
      const Table* table;
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
