#ifndef MidiFileHPP
#define MidiFileHPP

#include <Midi/MidiFile.h>

#include <Midi/MidiFileReader.h>
#include <Midi/MidiFileWriter.h>

Sequencer Midi::File::load(const Bytes& content)
{
   Midi::File::Reader reader(content);
   return reader;
}

Bytes Midi::File::save(const Sequencer& seqeuencer)
{
   return Bytes();
}

#endif // NOT MidiFileHPP
