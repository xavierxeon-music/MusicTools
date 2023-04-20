#ifndef SampleH
#define SampleH

#include <MusicTools.h>

class Sample
{
public:
   struct Meta
   {
      uint8_t noOfChannels = 1;
      uint16_t sampleRate = 1;
      size_t numberOfSamples = 0;
   };

   inline static Data load(const std::string& fileName, Meta* meta = nullptr);
   inline static bool save(const std::string& fileName, const Meta& meta, const Data& data);

   inline static Data interlace(const std::vector<Data> input);
   inline static std::vector<Data> deinterlace(const Data& input, const uint8_t numberOfChannels = 2);

   class Oscilator;
   class Recorder;

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
