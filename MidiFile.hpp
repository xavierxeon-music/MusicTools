#ifndef MidiFileHPP
#define MidiFileHPP

#include <Midi/MidiFile.h>

Midi::Sequence::Sequence()
   : ticksPer16(1)
   , uSecsPerQuarter(500000) // 120 bpm
   , trackList()
{
}

Midi::Sequence::Info Midi::Sequence::compileInfo() const
{
   Info info;

   info.bpm = 60000000 / uSecsPerQuarter;

   for (const Track& track : trackList)
   {
      if (info.maxTick < track.maxTick)
         info.maxTick = track.maxTick;
   }

   info.barCounter = info.maxTick / (16 * ticksPer16);

   const float beatCounter = 4 * info.barCounter;
   const float beatsPerSecond = static_cast<float>(info.bpm) / 60.0;
   const uint64_t totalSeconds = static_cast<uint64_t>(beatCounter / beatsPerSecond);
   info.seconds = totalSeconds % 60;
   info.minutes = (totalSeconds - info.seconds) / 60;

   return info;
}

const Midi::Sequence::Track::List& Midi::Sequence::getTrackList() const
{
   return trackList;
}

uint64_t Midi::Sequence::compileBarCounter(uint64_t trackIndex) const
{
   const Track& track = trackList.at(trackIndex);
   const uint64_t barCounter = track.maxTick / (16 * ticksPer16);

   return barCounter;
}

TimeCode::Duration Midi::Sequence::fromTick(const Tick& tick)
{
   TimeCode::Duration duration = tick / ticksPer16;
   return duration;
}

Midi::Sequence::Tick Midi::Sequence::toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat)
{
   const float fDuration = static_cast<float>(duration) + precentageToNextBeat;
   const float fTicks = fDuration * ticksPer16;
   const Tick tick = static_cast<Tick>(fTicks);

   return tick;
}

#endif // NOT MidiFileHPP
