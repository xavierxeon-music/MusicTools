#ifndef AudioFileH
#define AudioFileH

#include <MusicTools.h>

// see http://soundfile.sapp.org/doc/WaveFormat/

// pcm wav files
class AudioFile
{
public:
   inline AudioFile();

public:
   inline bool load(const std::string& fileName);
   inline bool save(const std::string& fileName);

public:
   uint16_t sampleRate;
   std::vector<float> leftData;
   std::vector<float> rightData;

private:
   struct Header
   {
      // RIFF Chunk Descriptor
      uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
      uint32_t chunkSize;                     // RIFF Chunk Size
      uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
      // "fmt" sub-chunk
      uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
      uint32_t Subchunk1Size;                // Size of the fmt chunk
      uint16_t audioFormat;                  // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
      uint16_t numChannels;                  // Number of channels 1=Mono 2=Stereo
      uint32_t sampleRate;                   // Sampling Frequency in Hz
      uint32_t bytesPerSec;                  // bytes per second
      uint16_t blockAlign;                   // 2=16-bit mono, 4=16-bit stereo
      uint16_t bitsPerSample;                // Number of bits per sample
      // "data" sub-chunk
      uint8_t subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
      uint32_t subchunk2Size;                        // Sampled data length

      Header();
   };
};

#ifndef AudioFileHPP
#include "../../AudioFile.hpp"
#endif // NOT AudioFileHPP

#endif // NOT AudioFileH
