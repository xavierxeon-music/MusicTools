#ifndef MidiFileH
#define MidiFileH

#include <map>

#include <Midi/MidiCommon.h>
#include <Music/TimeCode.h>

// see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

pyexport namespace Midi
{
   class Sequence
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

      pyexport struct Track
      {
         pyexport Tick maxTick = 0;
         pyexport std::string name;
         pyexport bool isMonophonic = false;

         using MessageList = std::vector<Bytes>;
         using TimeMessageMap = std::map<Tick, MessageList>;

         pyexport TimeMessageMap messageMap;

         using List = std::vector<Track>;
      };

   public:
      pyexport inline Sequence();

   public:
      pyexport inline Info compileInfo() const;
      pyexport inline const Track::List& getTrackList() const;
      pyexport inline uint64_t compileBarCounter(uint64_t trackIndex) const;

      pyexport inline TimeCode::Duration fromTick(const Tick& tick);
      pyexport inline Tick toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat = 0);

   protected:
      struct Chunk
      {
         std::string id;
         Bytes data;

         using List = std::vector<Chunk>;
      };

   protected:
      uint16_t ticksPer16;
      uint64_t uSecsPerQuarter; // only relevant to get file bpm
      Track::List trackList;
   };

   pyexport namespace File
   {
      class Reader;
      class Writer;

      const static bool verbose = true;
   };

} // namespace Midi

#ifndef MidiFileHPP
#include "../../MidiFile.hpp"
#endif // NOT MidiFileHPP

#endif // NOT MidiFileH
