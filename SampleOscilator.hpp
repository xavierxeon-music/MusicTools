#ifndef SampleOscilatorHPP
#define SampleOscilatorHPP

#include <Sound/SampleOscilator.h>

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
   , current()
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

   metaData.noOfChannels = header.numChannels;
   metaData.sampleRate = header.sampleRate;
   metaData.numberOfSamples = (8 * (header.chunkSize - 36)) / header.bitsPerSample;

   systemNumberOfSamples = metaData.numberOfSamples * systemSampleRate / metaData.sampleRate;

   if (buffered)
   {
      sampleBuffer = Data(metaData.numberOfSamples);

      int16_t rawBuffer;
      for (size_t counter = 0; counter < metaData.numberOfSamples; counter++)
      {
         const size_t br = fread(&rawBuffer, 1, sizeof(int16_t), wavFile);
         (void)br;

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
      current = Data(metaData.noOfChannels, 0.0);
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

      current = Data(metaData.noOfChannels, 0.0);
      return 0.0;
   }

   const uint8_t length = metaData.noOfChannels;
   current = read(samplePlayhead, length);

   auto advanceSystemPlayhead = [&]()
   {
      systemPlayhead += metaData.noOfChannels * playbackSpeed;
      if (systemPlayhead >= systemNumberOfSamples)
         systemPlayhead -= systemNumberOfSamples;
   };

   advanceSystemPlayhead();

   const float value = current.at(0);
   return value;
}

float Sample::Oscilator::getSound(uint8_t channel)
{
   if (channel >= current.size())
      return 0.0;

   return current.at(channel);
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
         const size_t br = fread(&rawBuffer, 1, sizeof(int16_t), wavFile);
         (void)br;

         if (feof(wavFile))
            fseek(wavFile, sizeof(WavHeader), SEEK_SET);

         const float value = static_cast<float>(rawBuffer) / maxValue;
         data[counter] = value;
      }
   }

   return data;
}

#endif // NOT SampleOscilatorHPP
