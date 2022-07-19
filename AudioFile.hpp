#ifndef AudioFileHPP
#define AudioFileHPP

#include <Sound/AudioFile.h>

#include <iostream>

AudioFile::AudioFile()
   : header{}
   , content{}
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

   size_t bytesRead = fread(&header, 1, sizeof(Header), wavFile);
   std::cout << "Header Read " << bytesRead << " bytes." << std::endl;

   uint16_t bytesPerSample = header.bitsPerSample / 8;      //Number     of bytes per sample
   uint64_t numSamples = header.ChunkSize / bytesPerSample; //How many samples are in the wav file?

   std::cout << "RIFF header                :" << header.RIFF[0] << header.RIFF[1] << header.RIFF[2] << header.RIFF[3] << std::endl;
   std::cout << "WAVE header                :" << header.WAVE[0] << header.WAVE[1] << header.WAVE[2] << header.WAVE[3] << std::endl;
   std::cout << "FMT                        :" << header.fmt[0] << header.fmt[1] << header.fmt[2] << header.fmt[3] << std::endl;
   std::cout << "Data size                  :" << header.ChunkSize << std::endl;

   // Display the sampling Rate from the header
   std::cout << "Sampling Rate              :" << header.SamplesPerSec << std::endl;
   std::cout << "Number of bits used        :" << header.bitsPerSample << std::endl;
   std::cout << "Number of channels         :" << header.NumOfChan << std::endl;
   std::cout << "Number of bytes per second :" << header.bytesPerSec << std::endl;
   std::cout << "Data length                :" << header.Subchunk2Size << std::endl;
   std::cout << "Audio Format               :" << header.AudioFormat << std::endl;
   // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

   std::cout << "Block align                :" << header.blockAlign << std::endl;
   std::cout << "Data string                :" << header.Subchunk2ID[0] << header.Subchunk2ID[1] << header.Subchunk2ID[2] << header.Subchunk2ID[3] << std::endl;

   return true;
}

bool AudioFile::save(const std::string& fileName)
{
   (void)fileName;

   return false;
}

#endif // NOT AudioFileHPP
