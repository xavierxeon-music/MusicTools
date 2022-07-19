#ifndef AudioFileHPP
#define AudioFileHPP

#include <Sound/AudioFile.h>

#include <iostream>

static const uint16_t BUFFER_SIZE = 4096;

// header

AudioFile::Header::Header()
{
   Subchunk1Size = 16; // default for PCM
   audioFormat = 1;
   numChannels = 2;
   sampleRate = 48000;
   bitsPerSample = 32;

   bytesPerSec = sampleRate * numChannels * bitsPerSample / 8;
   blockAlign = numChannels * bitsPerSample / 8;

   chunkSize = 0;     // RIFF Chunk Size
   subchunk2Size = 0; // Sampled data length
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
   std::cout << "Header Read " << bytesRead << " bytes." << std::endl;

   if (bytesRead <= 0)
      return false;

   std::cout << "RIFF header                :" << header.RIFF[0] << header.RIFF[1] << header.RIFF[2] << header.RIFF[3] << std::endl;
   std::cout << "WAVE header                :" << header.WAVE[0] << header.WAVE[1] << header.WAVE[2] << header.WAVE[3] << std::endl;
   std::cout << "FMT                        :" << header.fmt[0] << header.fmt[1] << header.fmt[2] << header.fmt[3] << std::endl;
   std::cout << "Data size                  :" << header.chunkSize << std::endl;

   // Display the sampling Rate from the header
   std::cout << "Sampling Rate              :" << header.sampleRate << std::endl;
   std::cout << "Number of bits used        :" << header.bitsPerSample << std::endl;
   std::cout << "Number of channels         :" << header.numChannels << std::endl;
   std::cout << "Number of bytes per second :" << header.bytesPerSec << std::endl;
   std::cout << "Data length                :" << header.subchunk2Size << std::endl;
   std::cout << "Audio Format               :" << header.audioFormat << std::endl;
   // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

   std::cout << "Block align                :" << header.blockAlign << std::endl;
   std::cout << "Data string                :" << header.subchunk2ID[0] << header.subchunk2ID[1] << header.subchunk2ID[2] << header.subchunk2ID[3] << std::endl;

   leftData.clear();
   rightData.clear();

   uint16_t bytesPerSample = header.bitsPerSample / 8;      //Number     of bytes per sample
   uint64_t numSamples = header.chunkSize / bytesPerSample; //How many samples are in the wav file?

   int8_t buffer[BUFFER_SIZE];
   while (true)
   {
      bytesRead = fread(buffer, sizeof(buffer[0]), BUFFER_SIZE / (sizeof buffer[0]), wavFile);
      if (bytesRead <= 0)
         break;

      /** DO SOMETHING WITH THE WAVE DATA HERE **/
      std::cout << "Read " << bytesRead << " bytes." << std::endl;
   }

   fclose(wavFile);

   return true;
}

bool AudioFile::save(const std::string& fileName)
{
   (void)fileName;

   return false;
}

#endif // NOT AudioFileHPP
