#ifndef SequencerH
#define SequencerH

#include <map>

#include <MusicTools.h>

#include <Music/TimeCode.h>

class Sequencer
{
public:
   using Tick = uint64_t;

   pyexport struct Info
   {
      Tick maxTick = 0;
      uint64_t barCounter = 0;
      uint16_t bpm = 0;
      uint32_t minutes = 0;
      uint8_t seconds = 0;

      std::vector<uint32_t> polyphonicTrackIndexList;
      std::vector<uint32_t> monophonicTrackIndexList;
   };

   pyexport struct Track
   {
      pyexport struct Header
      {
         Tick maxTick = 0;
         std::string name;

         using List = std::vector<Header>;
      };

      pyexport struct NoteEvent
      {
         uint8_t channel = 0;
         uint8_t key = 0;
         uint8_t velocity = 0;
         bool on = false;

         using List = std::vector<NoteEvent>;
         using TimeMap = std::map<Tick, List>;
      };

      Header header;

      NoteEvent::TimeMap noteOnEventMap;
      NoteEvent::TimeMap noteOffEventMap;

      using List = std::vector<Track>;
   };

public:
   pyexport inline Sequencer();

public:
   pyexport inline Info compileInfo() const;
   pyexport inline const Track::List& getTrackList() const;
   pyexport inline uint64_t compileBarCounter(uint64_t trackIndex) const;

   pyexport inline TimeCode::Duration fromTick(const Tick& tick);
   pyexport inline Tick toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat = 0);

protected:
   uint16_t ticksPer16;
   uint64_t uSecsPerQuarter; // only relevant to get file bpm
   Track::List trackList;
};

#ifndef SequencerHPP
#include "../../Sequencer.hpp"
#endif // NOT SequencerHPP

#endif // NOT SequencerH
