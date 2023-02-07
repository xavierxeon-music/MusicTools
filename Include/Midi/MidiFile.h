#ifndef MidiFileH
#define MidiFileH

#include <map>

#include <Midi/MidiCommon.h>
#include <Music/TimeCode.h>

namespace Midi
{
   class Sequence
   {
   public:
      using Tick = uint64_t;
      using MessageList = std::vector<Bytes>;
      using TimeMessageMap = std::map<Tick, MessageList>;

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
      uint16_t ticksPer16;
      uint64_t uSecsPerQuarter; // only relevant to get file bpm
      Track::List trackList;
   };

   namespace File
   {
      // see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

      class Reader : public Sequence
      {
      public:
         static const bool verbose = false;

      public:
         inline Reader(const Bytes& content);

      private:
         struct Chunk
         {
            std::string id;
            Bytes data;

            using List = std::vector<Chunk>;
         };

      private:
         // workflow
         inline void readHeader(const Chunk& headerChunk);
         inline void readTrack(const Chunk& trackChunk);
         inline MetaEvent readMetaEventAndAdvanceCursor(const Bytes& trackChunkData, uint64_t& cursor, Track* track);
         inline uint8_t compileMidiEventLength(const uint8_t marker) const;

         inline uint64_t variableLength(const Bytes& data, uint64_t& cursor) const;
         inline void updateMonophonicFlag();
      };
   } // namespace File
} // namespace Midi

#ifndef MidiFileHPP
#include "../../MidiFile.hpp"
#endif // NOT MidiFileHPP

#endif // NOT MidiFileH
