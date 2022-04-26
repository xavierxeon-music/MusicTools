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
      static float frequencyFromCV(float voltage);
      virtual float createSound() = 0;
   };
} // namespace Abstract

#endif //  AbstractOscilatorH
