#ifndef SampleOscilatorH
#define SampleOscilatorH

#include <Abstract/AbstractOscilator.h>
#include <Sound/Sample.h>

PYCLASS(Sample::Oscilator)

// wav file only!
class Sample::Oscilator : public Abstract::Oscilator
{
public:
   pyexport inline Oscilator(const bool buffered = true);
   inline ~Oscilator();

public:
   pyexport inline const Meta& getMeta() const;
   pyexport inline size_t getSamplePlayhead() const;
   pyexport inline float getPlaybackSpeed() const;

   pyexport inline void start();
   pyexport inline void pause();
   pyexport inline void reset();

   pyexport inline bool isLooping() const; // default true
   pyexport inline void setLooping(bool on);

   pyexport inline bool setFrequency(const float& newFrequency) override;

   pyexport inline void init(const std::string& fileName, const float& newSampleRate, const float newSampleFrequency = defaultFrequency); // system sample rate, NOT sampe rate of file!
   pyexport inline float createSound() override;                                                                                          // left channel
   pyexport inline float getSound(uint8_t channel = 1);                                                                                   // channel 0 is left, same as createSound()

private:
   enum class State
   {
      Pause,
      Play,
      Past // beyond loop
   };

private:
   inline Data read(const size_t& position, const size_t& numberOfSamples);

private:
   FILE* wavFile;
   Meta metaData;
   State state;
   bool loop;

   float systemPlayhead;
   float systemSampleRate;
   size_t systemNumberOfSamples;

   size_t samplePlayhead;
   float sampleFrequency;
   Data sampleBuffer;

   //
   float playbackSpeed;
   const bool buffered;
   Data current;
};

#ifndef SampleOscilatorHPP
#include "../../SampleOscilator.hpp"
#endif // NOT SampleOscilatorHPP

#endif // NOT SampleOscilatorH
