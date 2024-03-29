#ifndef AbstractEffectH
#define AbstractEffectH

#include <MusicTools.h>

#include <atomic>
#include <mutex>
#include <thread>

enum class FilterMode
{
   Off,
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

#ifdef NON_DAISY_DEVICE
   class ThreadeBufferEffect : public Effect
   {
   public:
      ThreadeBufferEffect(const uint16_t& bufferSize);
      virtual ~ThreadeBufferEffect();

   public:
      const uint16_t& getBufferSize() const;
      float changeSound(const float& in) override final;
      virtual Data proccessBuffer(const Data& input) = 0;
      void clear();

   private:
      void run();

   private:
      const uint16_t bufferSize;
      uint16_t bufferPosition;
      uint16_t writeBufferIndex;
      Data buffer[3];

      std::mutex processMutex;
      uint16_t processBufferIndex;
      std::atomic_bool stopThread;
      std::thread thread;
   };
#endif //  NON_DAISY_DEVICE

} // namespace Abstract

#endif //  AbstractEffectH
