#ifndef SampleHPP
#define SampleHPP

#include <Sound/Sample.h>

#include <limits>

#ifdef NON_DAISY_DEVICE
#include <iostream>
#endif // NON_DAISY_DEVICE

static const float maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());

// audio file

Data Sample::load(const std::string& fileName, Meta* meta)
{
   // TODO: support other formats than wav
   return loadWav(fileName, meta);
}

bool Sample::save(const std::string& fileName, const Meta& meta, const Data& data)
{
   // TODO: support other formats than wav
   return saveWav(fileName, meta, data);
}

Data Sample::interlace(const std::vector<Data> input)
{
   const uint8_t numberOfChannels = input.size();
   const size_t numberOfSamples = input.at(0).size();

   Data output;
   for (size_t inIndex = 0; inIndex < numberOfSamples; inIndex++)
   {
      for (uint8_t channel = 0; channel < numberOfChannels; channel++)
      {
         const Data& channelData = input.at(channel);
         const float value = channelData.at(inIndex);
         output.push_back(value);
      }
   }
   return output;
}

std::vector<Data> Sample::deinterlace(const Data& input, const uint8_t numberOfChannels)
{
   std::vector<Data> output(numberOfChannels, Data());
   if (0 != input.size() % numberOfChannels)
      return output;

   const size_t numberOfSamples = input.size() / numberOfChannels;
   for (size_t outIndex = 0; outIndex < numberOfSamples; outIndex++)
   {
      for (uint8_t channel = 0; channel < numberOfChannels; channel++)
      {
         const size_t inIndex = channel + (outIndex * numberOfChannels);
         const float value = input[inIndex];
         output[channel].push_back(value);
      }
   }

   return output;
}

// wav file functions

struct Sample::WavHeader
{
   // RIFF Chunk Descriptor
   uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
   uint32_t chunkSize = 0;                 // RIFF Chunk Size
   uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
   // "fmt" sub-chunk
   uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
   uint32_t subchunk1Size = 0;            // Size of the fmt chunk
   uint16_t audioFormat = 1;              // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
   uint16_t numChannels = 2;              // Number of channels 1=Mono 2=Stereo
   uint32_t sampleRate = 41000;           // Sampling Frequency in Hz
   uint32_t bytesPerSec = 0;              // bytes per second
   uint16_t blockAlign = 0;               // 2=16-bit mono, 4=16-bit stereo
   uint16_t bitsPerSample = 16;           // Number of bits per sample
   // "data" sub-chunk
   uint8_t subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
   uint32_t dataSize = 0;                         // Sampled data length
};

Data Sample::loadWav(const std::string& fileName, Meta* meta)
{
   if (meta)
   {
      meta->noOfChannels = 1;
      meta->sampleRate = 1;
      meta->numberOfSamples = 0;
   }

   FILE* wavFile = fopen(fileName.c_str(), "r");
   if (wavFile == nullptr)
   {
      // fprintf(stderr, "Unable to open wave file: %s\n", filePath);
      return Data();
   }

   WavHeader header;
   size_t bytesRead = fread(&header, 1, sizeof(WavHeader), wavFile);
   if (bytesRead <= 0)
      return Data();

   if (header.audioFormat != 1 || header.bitsPerSample != 16)
      return Data();

   if (meta)
   {
      meta->noOfChannels = header.numChannels;
      meta->sampleRate = header.sampleRate;
      meta->numberOfSamples = header.dataSize / (header.bitsPerSample / 8);
   }

   Data data;

   int16_t rawBuffer;
   while (true)
   {
      bytesRead = fread(&rawBuffer, 1, sizeof(int16_t), wavFile);
      if (bytesRead <= 0)
         break;

      const float value = static_cast<float>(rawBuffer) / maxValue;
      data.push_back(value);
   }

   fclose(wavFile);

   return data;
}

bool Sample::saveWav(const std::string& fileName, const Meta& meta, const Data& data)
{
   FILE* wavFile = fopen(fileName.c_str(), "w");
   if (wavFile == nullptr)
      return false;

   {
      WavHeader header;

      header.sampleRate = meta.sampleRate;
      header.numChannels = meta.noOfChannels;
      header.blockAlign = header.numChannels * (header.bitsPerSample / 8);
      header.bytesPerSec = header.sampleRate * header.blockAlign;

      header.dataSize = data.size();
      header.chunkSize = 36 + header.dataSize;

      fwrite(&header, 1, sizeof(WavHeader), wavFile);
   }
   for (const float& value : data)
   {
      const int16_t buffer = static_cast<int16_t>(value * maxValue);
      fwrite(&buffer, 1, sizeof(int16_t), wavFile);
   }

   fclose(wavFile);
   return true;
}

#endif // NOT SampleHPP
