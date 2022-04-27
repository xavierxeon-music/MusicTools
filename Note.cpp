#include <Music/Note.h>

#include <Maths.h>
#include <Tools/Range.h>

#include <map>

const Note Note::zeroNote = {"Z0", Note::Invalid, 0, -1.0f, 0.0f, 0};

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
            Note note;
            note.value = static_cast<Value>(voltageIndex);
            note.octave = octave;
            note.name = nameMap.at(note.value) + std::to_string(octave);

            note.voltage = octave + (voltageIndex / 12.0);
            const uint8_t freqOctave = static_cast<uint8_t>(note.voltage + 0.25);
            const float rest = (note.voltage - freqOctave) + 0.25;
            note.frequency = noteAFreq[freqOctave] * pow(2, rest);

            note.midiValue = midiValue;
            midiValue++;

            //qDebug() << QString::fromStdString(note.name) << note.midiValue << note.frequency << note.voltage;

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

const Note& Note::fromVoltage(float voltage)
{
   if (0.0f > voltage)
      return zeroNote;

   const float value = Range::clamp<float>(voltage, 0.0f, 10.0f);
   const uint8_t index = 1 + static_cast<uint8_t>(value * 12.0);
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
