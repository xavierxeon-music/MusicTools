#ifndef DelayLineH
#define DelayLineH

#include <Abstract/AbstractEffect.h>

#include <MusicTools.h>

template <uint32_t MaxSamples>
class DelayLine : public Abstract::Effect
{
public:
   inline DelayLine();

public:
   float changeSound(const float& in) override;
   void setDelay(const uint32_t& samples);
   void setDelay(const float& delayTimeInMilliSeconds, const float& sampleRate);
   void setFeedback(const float& factor);
   void setFeedbackEffect(Abstract::Effect* effect);
   void setFeedfront(const float& factor);
   void setFeedfrontEffect(Abstract::Effect* effect);

protected:
   float data[MaxSamples];
   uint32_t delay;
   uint32_t indexIn;
   float feedback;
   Abstract::Effect* feedbackEffect;
   float feedfront;
   Abstract::Effect* feedfrontEffect;
};

using DelayLineOne = DelayLine<48000>;
using DelayLineTen = DelayLine<480000>;

#ifndef DelayLineHPP
#include "../../DelayLine.hpp"
#endif // NOT DelayLineHPP

#endif // NOT DelayLineH
