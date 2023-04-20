#ifndef NoteH
#define NoteH

#include <MusicTools.h>

#include <map>

class Note
{
public:
   using List = std::vector<Note>;
   using Index = uint8_t;
   using Octave = uint8_t;

   enum Value : uint8_t //
   {
      C = 0,
      Cs,
      D,
      Ds,
      E,
      F,
      Fs,
      G,
      Gs,
      A,
      As,
      B,
      Invalid
   };

   static const Note zeroNote;       // an invalid note
   static const List availableNotes; // includes zero note
   static const Index maxNoteIndex;  // size of availableNotes

   using ColorMap = std::map<Value, Color>;
   static const ColorMap colorMap;

public:
   Note();

public:
   static const Note& fromVoltage(float voltage);
   static const Note& fromMidi(uint8_t midi);
   static const Note& fromFrequency(float frequency);

public:
   const std::string name;
   const Value value;
   const Octave octave;
   const float frequency;
   const float voltage;
   const uint8_t midiValue;

private:
   Note(std::string name, Value value, Octave octave, float frequency, float voltage, uint8_t midiValue);
};

#endif // NoteH
