#ifndef NoteH
#define NoteH

#include <MusicTools.h>

#include <map>

pyexport class Note
{
public:
   using List = std::vector<Note>;
   using Index = uint8_t;
   using Octave = uint8_t;

   pyexport enum Value : uint8_t //
   {
      C,
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

   pyexport static const Note zeroNote;       // an invalid note
   pyexport static const List availableNotes; // includes zero note
   pyexport static const Index maxNoteIndex;  // size of availableNotes

   using ColorMap = std::map<Value, Color>;
   pyexport static const ColorMap colorMap;

public:
   pyexport Note();

public:
   pyexport static const Note& fromVoltage(float voltage);
   pyexport static const Note& fromMidi(uint8_t midi);
   pyexport static const Note& fromFrequency(float frequency);

public:
   pyexport const std::string name;
   pyexport const Value value;
   pyexport const Octave octave;
   pyexport const float frequency;
   pyexport const float voltage;
   pyexport const uint8_t midiValue;

private:
   Note(std::string name, Value value, Octave octave, float frequency, float voltage, uint8_t midiValue);
};

#endif // NoteH
