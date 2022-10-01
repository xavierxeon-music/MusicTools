#include <Music/Note.h>

#include <Maths.h>
#include <Tools/Range.h>

#include <map>

const Note Note::zeroNote = Note();

const Note::List Note::availableNotes = []()
{
   Note::List noteList;
   noteList.push_back(zeroNote);

   using NameMap = std::map<Note::Value, std::string>;
   const NameMap nameMap = {
      {C, "C"},
      {Cs, "C#"},
      {D, "D"},
      {Ds, "D#"},
      {E, "E"},
      {F, "F"},
      {Fs, "F#"},
      {G, "G"},
      {Gs, "G#"},
      {A, "A"},
      {As, "A#"},
      {B, "B"},
   };

   const std::vector<float> noteAFreq = []()
   {
      float value = 0.25 * 55.0;

      std::vector<float> freq;
      freq.push_back(value);

      for (uint8_t index = 1; index < 21; index++)
      {
         value *= 2;
         freq.push_back(value);
      }
      return freq;
   }();

   auto fillNoteList = [&]()
   {
      uint8_t midiValue = 24;
      for (Octave octave = 0; octave < 20; octave++)
      {
         for (uint8_t voltageIndex = 0; voltageIndex < 12; voltageIndex++)
         {
            const Value value = static_cast<Value>(voltageIndex);
            const std::string name = nameMap.at(value) + std::to_string(octave);

            const float voltage = octave + (voltageIndex / 12.0);
            const uint8_t freqOctave = static_cast<uint8_t>(voltage + 0.25);
            const float rest = (voltage - freqOctave) + 0.25;
            const float frequency = noteAFreq[freqOctave] * pow(2, rest);

            Note note(name, value, octave, frequency, voltage, midiValue);
            midiValue++;

            noteList.push_back(note);
            if (note.frequency > 20000)
               return;
         }
      }
   };

   fillNoteList();
   return noteList;
}();
// clang-format on

const Note::Index Note::maxNoteIndex = availableNotes.size() - 1;

const Note::ColorMap Note::colorMap = {{Note::C, Color{255, 255, 255}},
                                       {Note::Cs, Color{90, 90, 90}},
                                       {Note::D, Color{255, 0, 0}},
                                       {Note::Ds, Color{90, 0, 0}},
                                       {Note::E, Color{255, 30, 200}},
                                       {Note::F, Color{0, 0, 255}},
                                       {Note::Fs, Color{0, 0, 90}},
                                       {Note::G, Color{0, 255, 0}},
                                       {Note::Gs, Color{0, 90, 0}},
                                       {Note::A, Color{255, 255, 0}},
                                       {Note::As, Color{90, 90, 0}},
                                       {Note::B, Color{0, 0, 0}}};

// note

Note::Note()
   : name("Z0")
   , value(Note::Invalid)
   , octave(0)
   , frequency(-1.0f)
   , voltage(0.0f)
   , midiValue(0)
{
}

const Note& Note::fromVoltage(float voltage)
{
   if (0.0f > voltage)
      return zeroNote;

   const float value = Range::clamp<float>(voltage, 0.0f, 10.0f) * 12.0;
   const uint8_t index = 1 + static_cast<uint8_t>(value);
   if (index >= maxNoteIndex)
      return availableNotes[maxNoteIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromMidi(uint8_t midi)
{
   if (0 == midi)
      return zeroNote;

   const uint8_t index = 1 + midi - availableNotes.at(1).midiValue;
   if (index >= maxNoteIndex)
      return availableNotes[maxNoteIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromFrequency(float frequency)
{
   static const float minFrequency = availableNotes[1].frequency;
   static const float maxFrequency = availableNotes[maxNoteIndex].frequency;

   if (frequency < minFrequency)
      return Note::zeroNote;

   frequency = Range::clamp<float>(frequency, minFrequency, maxFrequency);
   const float expo = frequency / minFrequency;
   const float voltage = log2(expo);

   const Note& note = fromVoltage(voltage);
   return note;
}

Note::Note(std::string name, Value value, Octave octave, float frequency, float voltage, uint8_t midiValue)
   : name(name)
   , value(value)
   , octave(octave)
   , frequency(frequency)
   , voltage(voltage)
   , midiValue(midiValue)
{
}
