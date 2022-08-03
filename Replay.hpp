#ifndef ReplayHPP
#define ReplayHPP

#include <Blocks/Replay.h>

Replay::Replay()
   : ticksPer16(0)
   , uSecsPerQuarter(500000) // 120 bpm
   , trackList()
{
}

Replay::Info Replay::compileInfo() const
{
   Info info;

   info.bpm = 60000000 / uSecsPerQuarter;

   uint64_t endOfProjectTick = 0;
   for (const Track& track : trackList)
   {
      if (endOfProjectTick < track.header.maxTick)
         endOfProjectTick = track.header.maxTick;
   }

   info.barCounter = endOfProjectTick / (16 * ticksPer16);

   const float beatCounter = 4 * info.barCounter;
   const float beatsPerSecond = static_cast<float>(info.bpm) / 60.0;
   const uint64_t totalSeconds = static_cast<uint64_t>(beatCounter / beatsPerSecond);
   info.seconds = totalSeconds % 60;
   info.minutes = (totalSeconds - info.seconds) / 60;

   return info;
}

Replay::TrackHeader::List Replay::compileTrackHeaderList() const
{
   TrackHeader::List content;

   for (const Track& track : trackList)
      content.push_back(track.header);

   return content;
}

uint64_t Replay::compileBarCounter(uint64_t trackIndex) const
{
   const Track& track = trackList.at(trackIndex);
   const uint64_t barCounter = track.header.maxTick / (16 * ticksPer16);

   return barCounter;
}

#endif // NOT ReplayHPP
