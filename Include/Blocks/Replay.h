#ifndef ReplayH
#define ReplayH

#include <map>

#include <MusicTools.h>

class Replay
{
public:
   struct TrackHeader
   {
      uint64_t maxTick = 0;
      std::string name;

      using List = std::vector<TrackHeader>;
   };

   struct Info
   {
      uint64_t barCounter = 0;
      uint32_t bpm = 0;
      uint32_t minutes = 0;
      uint8_t seconds = 0;
   };

public:
   inline Replay();

public:
   inline Info compileInfo() const;
   inline TrackHeader::List compileTrackHeaderList() const;
   inline uint64_t compileBarCounter(uint64_t trackIndex) const;

protected:
   using Time = size_t;

   struct NoteEvent
   {
      uint8_t channel = 0;
      uint8_t key = 0;
      uint8_t velocity = 0;

      using List = std::vector<NoteEvent>;
      using TimeMap = std::map<Time, List>;
   };

   struct Track
   {
      TrackHeader header;

      NoteEvent::TimeMap noteOnEventMap;
      NoteEvent::TimeMap noteOffEventMap;

      using List = std::vector<Track>;
   };

protected:
   uint16_t ticksPer16;
   uint32_t uSecsPerQuarter;
   Track::List trackList;
};

#ifndef ReplayHPP
#include "../../Replay.hpp"
#endif // NOT ReplayHPP

#endif // NOT ReplayH
