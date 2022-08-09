#ifndef SampleOscilatorH
#define SampleOscilatorH

#include <Abstract/AbstractOscilator.h>
#include <Sound/Sample.h>

// wav file only!
class Sample::Oscilator : public Abstract::Oscilator
{
public:
   inline Oscilator(const bool buffered = true);
   inline ~Oscilator();

public:
   inline const Meta& getMeta() const;
   inline size_t getSamplePlayhead() const;
   inline float getPlaybackSpeed() const;

   inline void start();
   inline void pause();
   inline void reset();

   inline bool isLooping() const; // default true
   inline void setLooping(bool on);

   inline bool setFrequency(const float& newFrequency) override;

   inline void init(const std::string& fileName, const float& newSampleRate, const float newSampleFrequency = defaultFrequency); // system sample rate, NOT sampe rate of file!
   inline float createSound() override;                                                                                          // left channel
   inline float getSound(uint8_t channel = 1);                                                                                   // channel 0 is left, same as createSound()

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
