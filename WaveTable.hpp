#ifndef WaveTableHPP
#define WaveTableHPP

#include <Sound/WaveTable.h>

#include <Tools/Range.h>

// table

WaveTable::AbstractTable::AbstractTable(const float maxAngle)
   : maxAngle(maxAngle)
{
}

const float& WaveTable::AbstractTable::getMaxAngle() const
{
   return maxAngle;
}

// step table

WaveTable::StepTable::StepTable(const uint64_t& noOfSteps, const float& maxAngle)
   : AbstractTable(maxAngle)
   , noOfSteps(noOfSteps)
   , anglePerStep(maxAngle / static_cast<float>(noOfSteps))
{
}

const uint64_t& WaveTable::StepTable::getNoOfSteps() const
{
   return noOfSteps;
}

uint64_t WaveTable::StepTable::stepIndexFromAngle(float angle) const
{
   while (angle < 0)
      angle += maxAngle;

   while (angle >= maxAngle)
      angle -= maxAngle;

   const uint64_t index = static_cast<uint64_t>(angle / anglePerStep);
   return index;
}

// step value table

WaveTable::StepValueTable::StepValueTable(const uint64_t tableSize)
   : StepTable(tableSize)
{
   data = new float[tableSize];
}

WaveTable::StepValueTable::~StepValueTable()
{
   delete[] data;
}

float WaveTable::StepValueTable::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return data[index];
}

// oscilator

WaveTable::Oscilator::Oscilator()
   : Abstract::Oscilator()
   , table(nullptr)
   , sampleRate(1.0f)
   , phase(0.0f)
   , frequency(50.00f)
   , amplitude(0.7f)
   , deltaPhase(0.0f)
{
}

void WaveTable::Oscilator::init(const AbstractTable* newTable, const float& newSampleRate)
{
   table = newTable;
   sampleRate = newSampleRate;

   compileDeltaPhase();
}

void WaveTable::Oscilator::setPhase(const float& newPhase)
{
   phase = newPhase;

   while (phase > table->getMaxAngle())
      phase -= table->getMaxAngle();
   while (phase < 0)
      phase += table->getMaxAngle();
}

const float& WaveTable::Oscilator::getPhase() const
{
   return phase;
}

void WaveTable::Oscilator::setFrequency(const float& newFrequency)
{
   if (frequency == newFrequency)
      return;

   if (0.0f >= newFrequency)
      frequency = 0.0f;
   else
   {
#ifndef NON_DAISY_DEVICE
      // clamp to range of D/A converters
      // * 1.0 = amplitude ~0.5
      // * 2.0 = amplitude ~0.8
      // * 5.0 = full amplitude
      frequency = Range::clamp<float>(newFrequency, 2.0f, 20000.0f);
#else
      frequency = newFrequency;
#endif // NON_DAISY_DEVICE
   }

   compileDeltaPhase();
}

void WaveTable::Oscilator::setCycleDuration(const float& cylceDuration)
{
   setFrequency(1.0 / cylceDuration);
}

const float& WaveTable::Oscilator::getFrequency() const
{
   return frequency;
}

void WaveTable::Oscilator::setAmplitude(const float& newAmplitude)
{
   amplitude = newAmplitude;
}

const float& WaveTable::Oscilator::getAmplitude() const
{
   return amplitude;
}

float WaveTable::Oscilator::createSound()
{
   if (!table || 0.0f == deltaPhase)
      return 0.0f;

   const float value = table->valueByAngle(phase);

   // advance phase
   phase += deltaPhase;
   while (phase > table->getMaxAngle())
      phase -= table->getMaxAngle();

   return value * amplitude;
}

void WaveTable::Oscilator::compileDeltaPhase()
{
   deltaPhase = (table->getMaxAngle() * frequency) / sampleRate;
}

#endif // NOT WaveTableHPP
