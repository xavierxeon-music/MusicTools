#ifndef SequencerHPP
#define SequencerHPP

#include <Blocks/Sequencer.h>

Sequencer::Sequencer()
   : ticksPer16(1)
   , uSecsPerQuarter(500000) // 120 bpm
   , trackList()
{
}

Sequencer::Info Sequencer::compileInfo() const
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

const Sequencer::Track::List& Sequencer::getTrackList() const
{
   return trackList;
}

uint64_t Sequencer::compileBarCounter(uint64_t trackIndex) const
{
   const Track& track = trackList.at(trackIndex);
   const uint64_t barCounter = track.maxTick / (16 * ticksPer16);

   return barCounter;
}

TimeCode::Duration Sequencer::fromTick(const Tick& tick)
{
   TimeCode::Duration duration = tick / ticksPer16;
   return duration;
}

Sequencer::Tick Sequencer::toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat)
{
   const float fDuration = static_cast<float>(duration) + precentageToNextBeat;
   const float fTicks = fDuration * ticksPer16;
   const Tick tick = static_cast<Tick>(fTicks);

   return tick;
}

void Sequencer::updateMonophonicFlag()
{
   for (Track& track : trackList)
   {
      uint64_t counterOn = 0;
      uint64_t counterOff = 0;

      uint32_t maxPoly = 0;
      uint32_t currentPoly = 0;

      for (Tick tick = 0; true; tick++)
      {
         if (track.noteOnEventMap.size() <= counterOn && track.noteOffEventMap.size() <= counterOff)
            break;

         if (track.noteOffEventMap.find(tick) != track.noteOffEventMap.end())
         {
            counterOff++;

            const Sequencer::Track::NoteEvent::List& eventList = track.noteOffEventMap.at(tick);
            currentPoly -= eventList.size();
         }

         if (track.noteOnEventMap.find(tick) != track.noteOnEventMap.end())
         {
            counterOn++;

            const Sequencer::Track::NoteEvent::List& eventList = track.noteOnEventMap.at(tick);
            currentPoly += eventList.size();
            if (currentPoly > maxPoly)
               maxPoly = currentPoly;
         }
      }

      track.isMonophonic = (maxPoly < 2);
   }
}

#endif // NOT SequencerHPP
