#ifndef WaveTableOscilatorHPP
#define WaveTableOscilatorHPP

#include <Sound/WaveTableOscilator.h>

#include <Sound/WaveTable.h>

WaveTable::Oscilator::Oscilator()
   : Abstract::Oscilator()
   , table(nullptr)
   , sampleRate(1.0f)
   , phase(0.0)
   , angle(0.0f)
   , deltaAngle(0.0f)
{
}

void WaveTable::Oscilator::init(const AbstractTable* newTable, const float& newSampleRate)
{
   table = newTable;
   sampleRate = newSampleRate;

   compileDeltaAngle();
}

void WaveTable::Oscilator::reset()
{
   angle = 0.0;
}

void WaveTable::Oscilator::setPhase(const float& newPhase)
{
   phase = newPhase * table->getMaxAngle();
   normalizeAngle(phase);
}

const float& WaveTable::Oscilator::getPhase() const
{
   return phase;
}

bool WaveTable::Oscilator::setFrequency(const float& newFrequency)
{
   if (Abstract::Oscilator::setFrequency(newFrequency))
      compileDeltaAngle();

   return true;
}

float WaveTable::Oscilator::createSound()
{
   if (!table || 0.0f == deltaAngle)
      return 0.0f;

   float currentAngle = angle + phase;
   normalizeAngle(currentAngle);
   const float value = table->valueByAngle(currentAngle);

   // advance angle
   angle += deltaAngle;
   normalizeAngle(angle);

   return value * amplitude;
}

void WaveTable::Oscilator::normalizeAngle(float& value)
{
   while (value > table->getMaxAngle())
      value -= table->getMaxAngle();
   while (value < 0)
      value += table->getMaxAngle();
}

void WaveTable::Oscilator::compileDeltaAngle()
{
   deltaAngle = (table->getMaxAngle() * frequency) / sampleRate;
}
#endif // NOT WaveTableOscilatorHPP
