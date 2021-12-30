#include <pybind11/pybind11.h>

#include <Music/Note.h>

void init_Note(pybind11::module_& module)
{
   pybind11::class_<Note> note(module, "Note");
   note.def_static("fromVoltage", &Note::fromVoltage);
   note.def_static("fromMidi", &Note::fromMidi);
   note.def_static("fromFrequency", &Note::fromFrequency);
   note.def_readonly("name", &Note::name);
   note.def_readonly("frequency", &Note::frequency);
   note.def_readonly("voltage", &Note::voltage);
   note.def_readonly("midiValue", &Note::midiValue);
   note.def_readonly_static("maxDuration", &Note::maxDuration);
   note.def_readonly_static("zeroNote", &Note::zeroNote);
   note.def_readonly_static("availableNotes", &Note::availableNotes);
   note.def_readonly_static("maxIndex", &Note::maxIndex);

   pybind11::class_<Note::TimeCode> timeCode(note, "TimeCode");
   timeCode.def(pybind11::init<>());
   timeCode.def(pybind11::init<Note::Duration, uint8_t, uint8_t>());
   timeCode.def("text", &Note::TimeCode::text);
   timeCode.def("toDuration", &Note::TimeCode::toDuration);
   timeCode.def_readonly("bar", &Note::TimeCode::bar);
   timeCode.def_readonly("quarter", &Note::TimeCode::quarter);
   timeCode.def_readonly("tick", &Note::TimeCode::tick);
}