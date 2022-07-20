#ifndef AudioFileHPP
#define AudioFileHPP

#include <Sound/AudioFile.h>

#include <limits>

#ifdef NON_DAISY_DEVICE
#include <iostream>
#endif // NON_DAISY_DEVICE

static const float maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());

// meta

AudioFile::Meta::Meta()
   : stereo(false)
   , sampleRate(0)
   , numberOfSamples(0)
{
}

// header

struct AudioFile::Header
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
   uint32_t dataSize;                             // Sampled data length

   inline Header();
#ifdef NON_DAISY_DEVICE
   inline void print();
#endif // NON_DAISY_DEVICE
};

AudioFile::Header::Header()
{
   numChannels = 2;
   sampleRate = 41000;
   dataSize = 0;

   // fixed
   bitsPerSample = 16;
   Subchunk1Size = 16; // default for PCM
   audioFormat = 1;
}

#ifdef NON_DAISY_DEVICE
void AudioFile::Header::print()
{
   std::cout << "header size                : " << sizeof(Header) << std::endl;
   std::cout << "Data length                : " << dataSize << std::endl;
   std::cout << "chunk size                 : " << chunkSize << std::endl;

   std::cout << std::endl;

   std::cout << "RIFF header                : " << RIFF[0] << RIFF[1] << RIFF[2] << RIFF[3] << std::endl;
   std::cout << "WAVE header                : " << WAVE[0] << WAVE[1] << WAVE[2] << WAVE[3] << std::endl;
   std::cout << "FMT                        : " << fmt[0] << fmt[1] << fmt[2] << fmt[3] << std::endl;

   std::cout << std::endl;

   // Display the sampling Rate from the header
   std::cout << "Sampling Rate              : " << sampleRate << std::endl;
   std::cout << "Number of bits used        : " << bitsPerSample << std::endl;
   std::cout << "Number of channels         : " << numChannels << std::endl;
   std::cout << "Number of bytes per second : " << bytesPerSec << std::endl;
   std::cout << "Audio Format               : " << audioFormat << std::endl;

   std::cout << std::endl;

   std::cout << "Block align                : " << blockAlign << std::endl;
   std::cout << "Data string                : " << subchunk2ID[0] << subchunk2ID[1] << subchunk2ID[2] << subchunk2ID[3] << std::endl;

   std::cout << "-----------------" << std::endl;
   std::cout << std::endl;
}
#endif // NON_DAISY_DEVICE

// input stream

AudioFile::InputStream::InputStream(const std::string& fileName)
   : wavFile(nullptr)
   , metaData()
{
   FILE* wavFile = fopen(fileName.c_str(), "r");
   if (wavFile == nullptr)
   {
      // TODO
   }

   auto closeAndExit = [&]()
   {
      fclose(wavFile);
      wavFile = nullptr;
   };

   Header header;
   size_t bytesRead = fread(&header, 1, sizeof(Header), wavFile);
   if (bytesRead <= 0)
   {
      closeAndExit();
      return;
   }

   if (header.audioFormat != 1 || header.bitsPerSample != 16)
   {
      closeAndExit();
      return;
   }

   metaData.stereo = (2 == header.numChannels);
   metaData.sampleRate = header.sampleRate;
   metaData.numberOfSamples = header.dataSize / (header.bitsPerSample / 8);
}

AudioFile::InputStream::~InputStream()
{
   if (wavFile)
   {
      fclose(wavFile);
      wavFile = nullptr;
   }
}

const AudioFile::Meta& AudioFile::InputStream::meta() const
{
   return metaData;
}

AudioFile::Data AudioFile::InputStream::read(size_t noOfBlocks)
{
   if (!wavFile)
      return Data();

   Data data;
   size_t bytesRead = 0;

   int16_t buffer;
   for (size_t counter = 0; counter < noOfBlocks; counter++)
   {
      bytesRead = fread(&buffer, 1, sizeof(int16_t), wavFile);
      if (bytesRead <= 0)
         break;

      const float value = static_cast<float>(buffer) / maxValue;
      data.push_back(value);
   }

   return data;
}

// audio file

AudioFile::Data AudioFile::load(const std::string& fileName, Meta* meta)
{
   if (meta)
   {
      meta->stereo = false;
      meta->sampleRate = 0;
   }

   FILE* wavFile = fopen(fileName.c_str(), "r");
   if (wavFile == nullptr)
   {
      // fprintf(stderr, "Unable to open wave file: %s\n", filePath);
      return Data();
   }

   Header header;
   size_t bytesRead = fread(&header, 1, sizeof(Header), wavFile);
   if (bytesRead <= 0)
      return Data();

   if (header.audioFormat != 1 || header.bitsPerSample != 16)
      return Data();

   if (meta)
   {
      meta->stereo = (2 == header.numChannels);
      meta->sampleRate = header.sampleRate;
      meta->numberOfSamples = header.dataSize / (header.bitsPerSample / 8);
   }

   Data data;

   int16_t buffer;
   while (true)
   {
      bytesRead = fread(&buffer, 1, sizeof(int16_t), wavFile);
      if (bytesRead <= 0)
         break;

      const float value = static_cast<float>(buffer) / maxValue;
      data.push_back(value);
   }

   fclose(wavFile);

   return data;
}

bool AudioFile::save(const std::string& fileName, const Meta& meta, const Data& data)
{
   FILE* wavFile = fopen(fileName.c_str(), "w");
   if (wavFile == nullptr)
      return false;

   size_t bytesWritten = 0;
   {
      Header header;

      header.sampleRate = meta.sampleRate;
      header.numChannels = meta.stereo ? 2 : 1;
      header.blockAlign = header.numChannels * (header.bitsPerSample / 8);
      header.bytesPerSec = header.sampleRate * header.blockAlign;

      header.dataSize = data.size();
      header.chunkSize = 36 + header.dataSize;

      bytesWritten = fwrite(&header, 1, sizeof(Header), wavFile);
   }
   for (const float& value : data)
   {
      const int16_t buffer = static_cast<int16_t>(value * maxValue);
      bytesWritten = fwrite(&buffer, 1, sizeof(int16_t), wavFile);
   }

   fclose(wavFile);
   return true;
}

#endif // NOT AudioFileHPP
