#ifndef AbstractEffectH
#define AbstractEffectH

#include <MusicTools.h>

enum class FilterMode
{
   LowPass,
   BandPass,
   HighPass,
   Notch,
   Peak
};

namespace Abstract
{
   class Effect
   {
   public:
      Effect();

   public:
      virtual float changeSound(const float &in) = 0;
   };

   class BufferedEffect : public Effect
   {
   public:
      BufferedEffect(const uint16_t &bufferSize);

   protected:
      virtual Data proccessBuffer(const Data &input) = 0;
      void clear();

   private:
      float changeSound(const float &in) override final;

   private:
      const uint16_t &bufferSize;
      uint16_t bufferIndex;
      Data inputBuffer;
      Data outputBuffer;
   };

} // namespace Abstract

#endif //  AbstractEffectH
