#ifndef WaveTableHPP
#define WaveTableHPP

#include <Sound/WaveTable.h>

#include <Tools/Range.h>

// table

WaveTable::Table::Table(const float maxAngle)
   : maxAngle(maxAngle)
{
}

WaveTable::Table::~Table()
{
}

const float& WaveTable::Table::getMaxAngle() const
{
   return maxAngle;
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

void WaveTable::Oscilator::init(const Table* newTable, const float& newSampleRate)
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

float WaveTable::Oscilator::frequencyFromCV(float voltage)
{
   static const float baseFreq[6] = {65.40639132514963f, 130.81278265029925f, 261.6255653005985f, 523.251130601197f, 1046.502261202394f, 2093.004522404789f};

   if (0.0f > voltage || 5.0f < voltage)
      return 0.0f;

   const uint8_t octave = static_cast<uint8_t>(voltage);
   const float rest = voltage - octave;
   const float frequency = baseFreq[octave] * pow(2, rest);

   return frequency;
}

void WaveTable::Oscilator::compileDeltaPhase()
{
   deltaPhase = (table->getMaxAngle() * frequency) / sampleRate;
}

#endif // NOT WaveTableHPP
