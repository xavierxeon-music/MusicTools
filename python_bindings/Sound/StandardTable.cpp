#include <pybind11/pybind11.h>

#include <Sound/StandardTable.h>

void init_StandardTable(pybind11::module_& module)
{
   pybind11::class_<Standard> standard(module, "Standard");
   standard.def_static("getName", &Standard::getName);
   standard.def_static("getTable", &Standard::getTable, pybind11::return_value_policy::reference);

   pybind11::class_<Standard::Waveform> waveform(standard, "Waveform");

   pybind11::enum_<Standard::Waveform::Shape> shape(waveform, "Shape");
   shape.value("Sine", Standard::Waveform::Sine);
   shape.value("Saw", Standard::Waveform::Saw);
   shape.value("Square", Standard::Waveform::Square);
   shape.value("SlopeUp", Standard::Waveform::SlopeUp);
   shape.value("SlopeDown", Standard::Waveform::SlopeDown);
   shape.export_values();
}