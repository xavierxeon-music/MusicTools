#ifndef AbstractEffectH
#define AbstractEffectH

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
