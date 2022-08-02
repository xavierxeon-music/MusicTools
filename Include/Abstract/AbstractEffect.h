#ifndef AbstractEffectH
#define AbstractEffectH

#include <thread>

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
      virtual ~Effect();

   public:
      virtual float changeSound(const float& in) = 0;
   };

   class BufferedEffect : public Effect
   {
   public:
      BufferedEffect(const uint16_t& bufferSize);
      virtual ~BufferedEffect();

   public:
      const uint16_t& getBufferSize() const;
      float changeSound(const float& in) override final;
      virtual Data proccessBuffer(const Data& input) = 0;
      void clear();

   private:
      const uint16_t bufferSize;
      uint16_t bufferPosition;
      Data inputBuffer;
      Data outputBuffer;
   };

   class ThreadeBufferEffect : public Effect
   {
      ThreadeBufferEffect(const uint16_t& bufferSize);
      virtual ~ThreadeBufferEffect();

   public:
      const uint16_t& getBufferSize() const;
      float changeSound(const float& in) override final;
      virtual Data proccessBuffer(const Data& input) = 0;
      void clear();

   private:
      const uint16_t bufferSize;
      uint16_t bufferPosition;
      uint8_t writeBufferIndex;
      Data buffer[3];
   };

} // namespace Abstract

#endif //  AbstractEffectH
