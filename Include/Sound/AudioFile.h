#ifndef AudioFileH
#define AudioFileH

#include <MusicTools.h>

// see http://soundfile.sapp.org/doc/WaveFormat/

// 16 bit PCM wav files
struct AudioFile
{
   struct Meta
   {
      bool stereo;
      uint16_t sampleRate;
      size_t numberOfSamples;

      inline Meta();
   };

   using Data = std::vector<float>;

   struct Header;

   class InputStream
   {
   public:
      inline InputStream(const std::string& fileName); // opens stream
      inline ~InputStream();

   public:
      inline const Meta& meta() const;
      inline Data read(size_t noOfBlocks);

   private:
      FILE* wavFile;
      Meta metaData;
   };

   inline static Data load(const std::string& fileName, Meta* meta = nullptr);
   inline static bool save(const std::string& fileName, const Meta& meta, const Data& data);
};

#ifndef AudioFileHPP
#include "../../AudioFile.hpp"
#endif // NOT AudioFileHPP

#endif // NOT AudioFileH
