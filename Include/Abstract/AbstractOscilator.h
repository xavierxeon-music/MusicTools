#ifndef AbstractOscilatorH
#define AbstractOscilatorH

#include "AbstractSoundSource.h"

namespace Abstract
{
   class Oscilator : public SoundSource
   {
   public:
      static const float defaultFrequency;

   public:
      Oscilator();
      virtual ~Oscilator();

   public:
      virtual bool setFrequency(const float& newFrequency);
      void setCycleDuration(const float& cylceDuration); // cylceDuration = 1.0 / frequency
      const float& getFrequency() const;
      static float frequencyFromCV(float voltage);

      virtual void setAmplitude(const float& newAmplitude);
      const float& getAmplitude() const;


   protected:
      float frequency;
      float amplitude;
   };
} // namespace Abstract

#endif //  AbstractOscilatorH
