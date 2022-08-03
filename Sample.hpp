#ifndef SampleHPP
#define SampleHPP

#include <Sound/Sample.h>

#include <limits>

#ifdef NON_DAISY_DEVICE
#include <iostream>
#endif // NON_DAISY_DEVICE

static const float maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());

// meta

Sample::Meta::Meta()
   : stereo(false)
   , sampleRate(1)
   , numberOfSamples(0)
{
}

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

// wav header

struct Sample::WavHeader
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

   inline WavHeader();
#ifdef NON_DAISY_DEVICE
   inline void print();
#endif // NON_DAISY_DEVICE
};

Sample::WavHeader::WavHeader()
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
void Sample::WavHeader::print()
{
   std::cout << "header size                : " << sizeof(WavHeader) << std::endl;
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

Sample::Oscilator::Oscilator(const bool buffered)
   : Abstract::Oscilator()
   , wavFile(nullptr)
   , metaData()
   , state(State::Pause)
   , loop(false)
   , systemPlayhead(0)
   , systemSampleRate(1.0)
   , systemNumberOfSamples(0)
   , samplePlayhead(0)
   , sampleFrequency(defaultFrequency)
   , sampleBuffer()
   , playbackSpeed(1.0)
   , buffered(buffered)
   , rightValue(0.0)
{
}

Sample::Oscilator::~Oscilator()
{
   if (wavFile)
   {
      fclose(wavFile);
      wavFile = nullptr;
   }
}

const Sample::Meta& Sample::Oscilator::getMeta() const
{
   return metaData;
}

size_t Sample::Oscilator::getSamplePlayhead() const
{
   return samplePlayhead;
}

float Sample::Oscilator::getPlaybackSpeed() const
{
   return playbackSpeed;
}

void Sample::Oscilator::start()
{
   state = State::Play;
}

void Sample::Oscilator::pause()
{
   state = State::Pause;
}

void Sample::Oscilator::reset()
{
   systemPlayhead = 0;
}

bool Sample::Oscilator::isLooping() const
{
   return loop;
}

void Sample::Oscilator::setLooping(bool on)
{
   loop = on;
}

bool Sample::Oscilator::setFrequency(const float& newFrequency)
{
   if (Abstract::Oscilator::setFrequency(newFrequency))
      playbackSpeed = frequency / sampleFrequency;

   return true;
}

void Sample::Oscilator::init(const std::string& fileName, const float& newSampleRate, const float newSampleFrequency)
{
   systemPlayhead = 0;
   systemSampleRate = newSampleRate;
   systemNumberOfSamples = 0;

   sampleBuffer.clear();
   samplePlayhead = 0;
   sampleFrequency = newSampleFrequency;

   wavFile = fopen(fileName.c_str(), "r");
   if (!wavFile)
   {
      // TODO
      return;
   }

   auto closeAndExit = [&]()
   {
      fclose(wavFile);
      wavFile = nullptr;
   };

   WavHeader header;
   size_t bytesRead = fread(&header, 1, sizeof(WavHeader), wavFile);
   if (bytesRead <= 0)
      return closeAndExit();

   if (header.audioFormat != 1 || header.bitsPerSample != 16)
      return closeAndExit();

   metaData.stereo = (2 == header.numChannels);
   metaData.sampleRate = header.sampleRate;
   metaData.numberOfSamples = header.dataSize / (header.bitsPerSample / 8);

   systemNumberOfSamples = metaData.numberOfSamples * systemSampleRate / metaData.sampleRate;

   if (buffered)
   {
      sampleBuffer = Data(metaData.numberOfSamples);

      int16_t rawBuffer;
      for (size_t counter = 0; counter < metaData.numberOfSamples; counter++)
      {
         fread(&rawBuffer, 1, sizeof(int16_t), wavFile);
         const float value = static_cast<float>(rawBuffer) / maxValue;
         sampleBuffer[counter] = value;
      }

      fclose(wavFile);
      wavFile = nullptr;
   }
}

float Sample::Oscilator::createSound()
{
   if (State::Play != state)
   {
      rightValue = 0.0;
      return 0.0;
   }

   const float ratio = metaData.sampleRate / systemSampleRate;
   const float fIndex = systemPlayhead * ratio;

   const size_t oldSamplePlayhead = samplePlayhead;
   samplePlayhead = static_cast<size_t>(fIndex);
   if (!loop && (samplePlayhead < oldSamplePlayhead))
   {
      state = State::Past;
      samplePlayhead = oldSamplePlayhead;

      rightValue = 0.0;
      return 0.0;
   }

   const uint8_t length = metaData.stereo ? 2 : 1;
   Data current = read(samplePlayhead, length);

   auto advanceSystemPlayhead = [&]()
   {
      systemPlayhead += playbackSpeed;
      if (systemPlayhead >= systemNumberOfSamples)
         systemPlayhead -= systemNumberOfSamples;
   };

   advanceSystemPlayhead();
   const float leftValue = current.at(0);

   if (metaData.stereo)
   {
      advanceSystemPlayhead();
      rightValue = current.at(1);
   }
   else
   {
      rightValue = leftValue;
   }

   return leftValue;
}

float Sample::Oscilator::rightSound()
{
   return rightValue;
}

Data Sample::Oscilator::read(const size_t& position, const size_t& numberOfSamples)
{
   Data data(numberOfSamples);
   if (buffered)
   {
      if (sampleBuffer.empty())
         return data;
      size_t samplePos = position;
      for (size_t counter = 0; counter < numberOfSamples; counter++)
      {
         data[counter] = sampleBuffer.at(samplePos);

         samplePos++;
         if (samplePos >= sampleBuffer.size())
            samplePos = 0;
      }
   }
   else
   {
      if (!wavFile)
         return data;

      int16_t rawBuffer;
      fseek(wavFile, 2 * position, SEEK_SET);
      for (size_t counter = 0; counter < numberOfSamples; counter++)
      {
         fread(&rawBuffer, 1, sizeof(int16_t), wavFile);

         if (feof(wavFile))
            fseek(wavFile, sizeof(WavHeader), SEEK_SET);

         const float value = static_cast<float>(rawBuffer) / maxValue;
         data[counter] = value;
      }
   }

   return data;
}

// wav file functions

Data Sample::loadWav(const std::string& fileName, Meta* meta)
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

   WavHeader header;
   size_t bytesRead = fread(&header, 1, sizeof(WavHeader), wavFile);
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
      header.numChannels = meta.stereo ? 2 : 1;
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
