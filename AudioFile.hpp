#ifndef AudioFileHPP
#define AudioFileHPP

#include <Sound/AudioFile.h>

#include <iostream>
#include <limits>

static const uint16_t BUFFER_SIZE = 4096;

// header

AudioFile::Header::Header()
{
   numChannels = 2;
   sampleRate = 41000;
   subchunk2Size = 0;

   // fixed
   bitsPerSample = 16;
   Subchunk1Size = 16; // default for PCM
   audioFormat = 1;
}

void AudioFile::Header::update()
{
   blockAlign = numChannels * (bitsPerSample / 8);
   bytesPerSec = sampleRate * blockAlign;
   chunkSize = 36 + subchunk2Size;
}

void AudioFile::Header::print()
{
   std::cout << "header size                : " << sizeof(Header) << std::endl;
   std::cout << "Data length                : " << subchunk2Size << std::endl;
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

// audio file

AudioFile::AudioFile()
   : sampleRate(48000)
   , leftData()
   , rightData()
{
}

bool AudioFile::load(const std::string& fileName)
{
   FILE* wavFile = fopen(fileName.c_str(), "r");
   if (wavFile == nullptr)
   {
      // fprintf(stderr, "Unable to open wave file: %s\n", filePath);
      return false;
   }

   Header header;
   size_t bytesRead = fread(&header, 1, sizeof(Header), wavFile);
   if (bytesRead <= 0)
      return false;

   if (header.audioFormat != 1 || header.bitsPerSample != 16)
      return false;

   sampleRate = header.sampleRate;
   leftData.clear();
   rightData.clear();

   static const float maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());
   static const size_t bufferSize = sizeof(int16_t);

   int16_t buffer;
   bool leftChannel = true;
   while (true)
   {
      bytesRead = fread(&buffer, 1, bufferSize, wavFile);
      if (bytesRead <= 0)
         break;

      const float value = static_cast<float>(buffer) / maxValue;
      if (1 == header.numChannels)
      {
         leftData.push_back(value);
      }
      else if (2 == header.numChannels)
      {
         if (leftChannel)
            leftData.push_back(value);
         else
            rightData.push_back(value);

         leftChannel ^= true;
      }
   }

   fclose(wavFile);

   std::cout << "read ok: " << leftData.size() << ", " << rightData.size() << std::endl;
   return true;
}

bool AudioFile::save(const std::string& fileName)
{
   (void)fileName;

   return false;
}

#endif // NOT AudioFileHPP
