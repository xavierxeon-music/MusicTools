#ifndef AbstractEffectH
#define AbstractEffectH

enum class FilterMode
{
   LowPass,
   BandPass,
   HighPass,
   Notch
};

namespace Abstract
{
   class Effect
   {
   public:
      Effect();

   public:
      virtual float changeSound(const float& in) = 0;
   };

} // namespace Abstract

#endif //  AbstractEffectH
