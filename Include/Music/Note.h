#ifndef NoteH
#define NoteH

#include <limits>

#include <MusicTools.h>

struct Note
{
public:
   using List = std::vector<Note>;
   using Duration = uint16_t;
   using Index = uint8_t;

   struct TimeCode
   {
      Duration bar;
      uint8_t quarter;
      uint8_t tick;

      TimeCode();
      TimeCode(Duration bar, uint8_t quarter, uint8_t tick = 0);
      TimeCode(const Duration& duration);

      std::string text() const;
      Duration toDuration() const;
   };

   static constexpr Duration maxDuration = std::numeric_limits<Note::Duration>::max() - 1;
   static const Note zeroNote;
   static const List availableNotes;
   static const Index maxIndex;

public:
   static const Note& fromVoltage(float voltage);
   static const Note& fromMidi(uint8_t midi);
   static const Note& fromFrequency(float frequency);

public:
   std::string name;
   float frequency;
   float voltage;
   uint8_t midiValue;
};

#endif // NoteH
