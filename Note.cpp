#include <Music/Note.h>

#include <Tools/Convert.h>
#include <Tools/Range.h>

// time code

Note::TimeCode::TimeCode()
   : bar(0)
   , quarter(0)
   , tick(0)
{
}

Note::TimeCode::TimeCode(Duration bar, uint8_t quarter, uint8_t tick)
   : bar(bar)
   , quarter(quarter)
   , tick(tick)
{
}

Note::TimeCode::TimeCode(const Duration& duration)
   : TimeCode()
{
   tick = duration % 4;
   quarter = ((duration - tick) / 4) % 4;
   bar = (((duration - tick) / 4) - quarter) / 4;
}

std::string Note::TimeCode::text() const
{
   if (0 == toDuration())
      return "-- - -";

   const std::string frontText = Convert::text(bar);
   const std::string midText = Convert::text(quarter);
   const std::string backText = Convert::text(tick);

   const std::string durationText = frontText + " " + midText + " " + backText;
   return durationText;
}

Note::Duration Note::TimeCode::toDuration() const
{
   const Duration duration = (16 * bar) + (4 * quarter) + tick;
   return duration;
}

// note

const Note Note::zeroNote = {"Z0", -1.0f, 0.0f, 0};

// clang-format off
const Note::List Note::availableNotes =
{
   Note::zeroNote ,
   {"C2", 65.40639132514963f, 0.0f, 36 },
   {"C#2", 69.295657744218f, 0.08333333333333333f, 37 },
   {"D2", 73.41619197935186f, 0.16666666666666666f, 38 },
   {"D#2", 77.7817459305202f, 0.25f, 39 },
   {"E2", 82.40688922821747f, 0.3333333333333333f, 40 },
   {"F2", 87.30705785825096f, 0.4166666666666667f, 41 },
   {"F#2", 92.49860567790859f, 0.5f, 42 },
   {"G2", 97.99885899543732f, 0.5833333333333334f, 43 },
   {"G#2", 103.82617439498628f, 0.6666666666666666f, 44 },
   {"A2", 110.0f, 0.75f, 45 },
   {"A#2", 116.54094037952248f, 0.8333333333333334f, 46 },
   {"B2", 123.47082531403103f, 0.9166666666666666f, 47 },
   {"C3", 130.81278265029925f, 1.0f, 48 },
   {"C#3", 138.591315488436f, 1.0833333333333333f, 49 },
   {"D3", 146.83238395870373f, 1.1666666666666667f, 50 },
   {"D#3", 155.5634918610404f, 1.25f, 51 },
   {"E3", 164.81377845643493f, 1.3333333333333333f, 52 },
   {"F3", 174.6141157165019f, 1.4166666666666667f, 53 },
   {"F#3", 184.99721135581717f, 1.5f, 54 },
   {"G3", 195.99771799087463f, 1.5833333333333333f, 55 },
   {"G#3", 207.65234878997256f, 1.6666666666666667f, 56 },
   {"A3", 220.0f, 1.75f, 57 },
   {"A#3", 233.08188075904496f, 1.8333333333333333f, 58 },
   {"B3", 246.94165062806206f, 1.9166666666666667f, 59 },
   {"C4", 261.6255653005985f, 2.0f, 60 },
   {"C#4", 277.182630976872f, 2.0833333333333335f, 61 },
   {"D4", 293.66476791740746f, 2.1666666666666665f, 62 },
   {"D#4", 311.1269837220808f, 2.25f, 63 },
   {"E4", 329.62755691286986f, 2.3333333333333335f, 64 },
   {"F4", 349.2282314330038f, 2.4166666666666665f, 65 },
   {"F#4", 369.99442271163434f, 2.5f, 66 },
   {"G4", 391.99543598174927f, 2.5833333333333335f, 67 },
   {"G#4", 415.3046975799451f, 2.6666666666666665f, 68 },
   {"A4", 440.0f, 2.75f, 69 },
   {"A#4", 466.1637615180899f, 2.8333333333333335f, 70 },
   {"B4", 493.8833012561241f, 2.9166666666666665f, 71 },
   {"C5", 523.251130601197f, 3.0f, 72 },
   {"C#5", 554.365261953744f, 3.0833333333333335f, 73 },
   {"D5", 587.3295358348149f, 3.1666666666666665f, 74 },
   {"D#5", 622.2539674441616f, 3.25f, 75 },
   {"E5", 659.2551138257397f, 3.3333333333333335f, 76 },
   {"F5", 698.4564628660077f, 3.4166666666666665f, 77 },
   {"F#5", 739.9888454232687f, 3.5f, 78 },
   {"G5", 783.9908719634985f, 3.5833333333333335f, 79 },
   {"G#5", 830.6093951598903f, 3.6666666666666665f, 80 },
   {"A5", 880.0f, 3.75f, 81 },
   {"A#5", 932.3275230361799f, 3.8333333333333335f, 82 },
   {"B5", 987.7666025122483f, 3.9166666666666665f, 83 },
   {"C6", 1046.502261202394f, 4.0f, 84 },
   {"C#6", 1108.730523907488f, 4.083333333333333f, 85 },
   {"D6", 1174.6590716696298f, 4.166666666666667f, 86 },
   {"D#6", 1244.5079348883232f, 4.25f, 87 },
   {"E6", 1318.5102276514795f, 4.333333333333333f, 88 },
   {"F6", 1396.9129257320153f, 4.416666666666667f, 89 },
   {"F#6", 1479.9776908465374f, 4.5f, 90 },
   {"G6", 1567.981743926997f, 4.583333333333333f, 91 },
   {"G#6", 1661.2187903197805f, 4.666666666666667f, 92 },
   {"A6", 1760.0f, 4.75f, 93 },
   {"A#6", 1864.6550460723597f, 4.833333333333333f, 94 },
   {"B6", 1975.5332050244965f, 4.916666666666667f, 95 },
   {"C7", 2093.0045224047894f, 5.0f, 96 }
};
// clang-format on

const Note::Index Note::maxIndex = availableNotes.size() - 1;

const Note& Note::fromVoltage(float voltage)
{
   if (0.0f > voltage)
      return zeroNote;

   const float value = Range::clamp<float>(voltage, 0.0f, 5.0f) / 5.0f;
   const uint8_t index = 1 + static_cast<uint8_t>(value * maxIndex);
   if (index >= maxIndex)
      return availableNotes[maxIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromMidi(uint8_t midi)
{
   if (0 == midi)
      return zeroNote;

   const uint8_t index = 1 + midi - availableNotes.at(1).midiValue;
   if (index >= maxIndex)
      return availableNotes[maxIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromFrequency(float frequency)
{
   static const float minFrequency = availableNotes[1].frequency;
   static const float maxFrequency = availableNotes[maxIndex].frequency;

   if (frequency < minFrequency)
      return Note::zeroNote;

   frequency = Range::clamp<float>(frequency, minFrequency, maxFrequency);
   const float expo = frequency / minFrequency;
   const float voltage = log2(expo);

   const Note& note = fromVoltage(voltage);
   return note;
}
