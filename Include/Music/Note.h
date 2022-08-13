#ifndef NoteH
#define NoteH

#include <MusicTools.h>

pyexport struct Note
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

public:
   pyexport static const Note& fromVoltage(float voltage);
   pyexport static const Note& fromMidi(uint8_t midi);
   pyexport static const Note& fromFrequency(float frequency);

public:
   pyexport std::string name;
   pyexport Value value;
   pyexport Octave octave;
   pyexport float frequency;
   pyexport float voltage;
   pyexport uint8_t midiValue;
};

#endif // NoteH
