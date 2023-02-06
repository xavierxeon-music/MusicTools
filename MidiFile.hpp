#ifndef MidiFileHPP
#define MidiFileHPP

#include <Midi/MidiFile.h>

#include <Midi/MidiFileReader.h>
#include <Midi/MidiFileWriter.h>

Sequencer Midi::FileOld::load(const Bytes& content)
{
   Midi::FileOld::Reader reader(content);
   return reader;
}

Bytes Midi::FileOld::save(const Sequencer& seqeuencer)
{
   return Bytes();
}

#endif // NOT MidiFileHPP
