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
   , bufferIndex(0)
   , inputBuffer(bufferSize, 0.0)
   , outputBuffer(bufferSize, 0.0)
{
}

Abstract::BufferedEffect::~BufferedEffect()
{
}

float Abstract::BufferedEffect::changeSound(const float& in)
{
   inputBuffer[bufferIndex] = in;
   const float out = outputBuffer[bufferIndex];

   bufferIndex++;
   if (bufferIndex >= bufferSize)
   {
      bufferIndex = 0;
      outputBuffer = proccessBuffer(inputBuffer);
   }

   return out;
}

void Abstract::BufferedEffect::clear()
{
   bufferIndex = 0;
   inputBuffer = Data(bufferSize, 0.0);
   outputBuffer = Data(bufferSize, 0.0);
}
