#ifndef SequencerH
#define SequencerH

#include <map>

#include <MusicTools.h>

#include <Music/TimeCode.h>

pyexport class Sequencer
{
public:
   using Tick = uint64_t;

   pyexport struct Info
   {
      pyexport Tick maxTick = 0;
      pyexport uint64_t barCounter = 0;
      pyexport uint16_t bpm = 0;
      pyexport uint32_t minutes = 0;
      pyexport uint8_t seconds = 0;
   };

   pyexport struct NoteEvent
   {
      pyexport uint8_t channel = 0;
      pyexport uint8_t midiNote = 0;
      pyexport bool on = false;
      pyexport uint8_t velocity = 0;

      inline NoteEvent();
      inline NoteEvent(const uint8_t channel, const uint8_t midiNote, const bool on, const uint8_t velocity = 0);
      inline NoteEvent(const NoteEvent& other);
      inline NoteEvent& operator=(const NoteEvent& other);
      inline bool operator==(const NoteEvent& other) const;
      inline bool operator!=(const NoteEvent& other) const;

      using List = std::vector<NoteEvent>;
      using TimeMap = std::map<Tick, List>;
   };

   pyexport struct Track
   {
      pyexport Tick maxTick = 0;
      pyexport std::string name;
      pyexport bool isMonophonic = false;

      pyexport NoteEvent::TimeMap noteOnEventMap;
      pyexport NoteEvent::TimeMap noteOffEventMap;

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
   inline void updateMonophonicFlag();

protected:
   uint16_t ticksPer16;
   uint64_t uSecsPerQuarter; // only relevant to get file bpm
   Track::List trackList;
};

#ifndef SequencerHPP
#include "../../Sequencer.hpp"
#endif // NOT SequencerHPP

#endif // NOT SequencerH
