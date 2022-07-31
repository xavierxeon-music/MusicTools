#ifndef AbstractOscilatorH
#define AbstractOscilatorH

namespace Abstract
{
   class Oscilator
   {
   public:
      Oscilator();
      virtual ~Oscilator();

   public:
      virtual void setFrequency(const float& newFrequency);
      void setCycleDuration(const float& cylceDuration); // cylceDuration = 1.0 / frequency
      const float& getFrequency() const;
      static float frequencyFromCV(float voltage);

      virtual void setAmplitude(const float& newAmplitude);
      const float& getAmplitude() const;

      virtual float createSound() = 0;

   protected:
      float frequency;
      float amplitude;
   };
} // namespace Abstract

#endif //  AbstractOscilatorH
