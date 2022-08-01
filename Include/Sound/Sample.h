#ifndef SampleH
#define SampleH

#include <Abstract/AbstractOscilator.h>

#include <MusicTools.h>

class Sample
{
public:
   struct Meta
   {
      bool stereo;
      uint16_t sampleRate;
      size_t numberOfSamples;

      inline Meta();
   };

   inline static Data load(const std::string& fileName, Meta* meta = nullptr);
   inline static bool save(const std::string& fileName, const Meta& meta, const Data& data);

   // wav file only!
   class Oscilator : public Abstract::Oscilator
   {
   public:
      inline Oscilator(const bool buffered = true);
      inline ~Oscilator();

   public:
      inline const Meta& getMeta() const;
      inline size_t getSamplePlayhead() const;
      inline float getPlaybackSpeed() const;

      inline void start();
      inline void pause();
      inline void reset();

      inline bool isLooping() const; // default true
      inline void setLooping(bool on);

      inline bool setFrequency(const float& newFrequency) override;

      inline void init(const std::string& fileName, const float& newSampleRate, const float newSampleFrequency = defaultFrequency); // system sample rate, NOT sampe rate of file!
      inline float createSound() override;                                                                                          // left channel
      inline float rightSound();

   private:
      enum class State
      {
         Pause,
         Play,
         Past // beyond loop
      };

   private:
      inline Data read(const size_t& position, const size_t& numberOfSamples);

   private:
      FILE* wavFile;
      Meta metaData;
      State state;
      bool loop;

      float systemPlayhead;
      float systemSampleRate;
      size_t systemNumberOfSamples;

      size_t samplePlayhead;
      float sampleFrequency;
      Data sampleBuffer;

      //
      float playbackSpeed;
      const bool buffered;
      float rightValue;
   };

private:
   // 16 bit PCM wav files
   // see http://soundfile.sapp.org/doc/WaveFormat/
   struct WavHeader;

private:
   inline static Data loadWav(const std::string& fileName, Meta* meta);
   inline static bool saveWav(const std::string& fileName, const Meta& meta, const Data& data);
};

#ifndef SampleHPP
#include "../../Sample.hpp"
#endif // NOT SampleHPP

#endif // NOT SampleH
