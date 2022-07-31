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
      inline Oscilator(); // opens stream
      inline ~Oscilator();

   public:
      void start();
      void stop();

      bool isLooping() const; // default true
      void setLooping(bool on);

      inline void init(const std::string& fileName, const float& newSampleRate, const float newSampleFrequency = 110.0); // system sample rate, NOT sampe rate of file!
      inline float createSound() override;

   private:
      inline Data read(size_t noOfBlocks);

   private:
      FILE* wavFile;
      Meta metaData;
      bool loop;
      float systemSampleRate;
      float sampleFrequency;
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
