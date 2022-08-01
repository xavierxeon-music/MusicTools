#ifndef AbstractSoundSourceH
#define AbstractSoundSourceH

namespace Abstract
{
   class SoundSource
   {
   public:
      SoundSource();
      virtual ~SoundSource();

   protected:
      virtual float createSound() = 0;
   };
} // namespace Abstract

#endif // NOT AbstractSoundSourceH
