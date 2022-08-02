#include <Abstract/AbstractEffect.h>

// effect

Abstract::Effect::Effect()
{
}

Abstract::Effect::~Effect()
{
}

// buffered effect

Abstract::BufferedEffect::BufferedEffect(const uint16_t& bufferSize)
   : Effect()
   , bufferSize(bufferSize)
   , bufferPosition(0)
   , inputBuffer(bufferSize, 0.0)
   , outputBuffer(bufferSize, 0.0)
{
}

Abstract::BufferedEffect::~BufferedEffect()
{
}

const uint16_t& Abstract::BufferedEffect::getBufferSize() const
{
   return bufferSize;
}

float Abstract::BufferedEffect::changeSound(const float& in)
{
   inputBuffer[bufferPosition] = in;
   const float out = outputBuffer[bufferPosition];

   bufferPosition++;
   if (bufferPosition >= bufferSize)
   {
      bufferPosition = 0;
      outputBuffer = proccessBuffer(inputBuffer);
   }

   return out;
}

void Abstract::BufferedEffect::clear()
{
   bufferPosition = 0;
   inputBuffer = Data(bufferSize, 0.0);
   outputBuffer = Data(bufferSize, 0.0);
}

// threaded bufferd effect

Abstract::ThreadeBufferEffect::ThreadeBufferEffect(const uint16_t& bufferSize)
   : Effect()
   , bufferSize(bufferSize)
   , bufferPosition(0)
   , writeBufferIndex(0)
   , buffer{Data(bufferSize, 0.0), Data(bufferSize, 0.0), Data(bufferSize, 0.0)}
   , processMutex()
   , processBufferIndex(3)
   , stopThread(false)
   , thread(&ThreadeBufferEffect::run, this)
{
}

Abstract::ThreadeBufferEffect::~ThreadeBufferEffect()
{
   {
      std::lock_guard<std::mutex> guard(processMutex);
      stopThread = true;
   }
   thread.join();
}

const uint16_t& Abstract::ThreadeBufferEffect::getBufferSize() const
{
   return bufferSize;
}

float Abstract::ThreadeBufferEffect::changeSound(const float& in)
{
   buffer[writeBufferIndex][bufferPosition] = in;

   const uint8_t readBufferIndex = (writeBufferIndex + 1) % 3;
   const float out = buffer[readBufferIndex][bufferPosition];

   bufferPosition++;
   if (bufferPosition >= bufferSize)
   {
      {
         std::lock_guard<std::mutex> guard(processMutex);
         processBufferIndex = (writeBufferIndex + 2) % 3;
      }
      bufferPosition = 0;
      writeBufferIndex = (writeBufferIndex + 1) % 3;
   }

   return out;
}

void Abstract::ThreadeBufferEffect::clear()
{
   bufferPosition = 0;
   writeBufferIndex = 0;
   buffer[0] = Data(bufferSize, 0.0);
   buffer[1] = Data(bufferSize, 0.0);
   buffer[2] = Data(bufferSize, 0.0);
}

void Abstract::ThreadeBufferEffect::run()
{
   while (true)
   {
      {
         std::lock_guard<std::mutex> guard(processMutex);

         if (stopThread)
            break;

         if (3 == processBufferIndex)
            continue;
      }

      buffer[processBufferIndex] = proccessBuffer(buffer[processBufferIndex]);

      {
         std::lock_guard<std::mutex> guard(processMutex);
         processBufferIndex = 3;
      }
   }
}
