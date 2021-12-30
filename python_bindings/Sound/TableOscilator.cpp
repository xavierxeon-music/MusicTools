#include <pybind11/pybind11.h>

#include <Sound/TableOscilator.h>

void init_TableOscilator(pybind11::module_& module)
{
   pybind11::class_<TableOscilator> tableOscilator(module, "TableOscilator");
   tableOscilator.def(pybind11::init<>());
   tableOscilator.def_property("phase", &TableOscilator::getPhase, &TableOscilator::setPhase);
   tableOscilator.def_property("frequency", &TableOscilator::getFrequency, &TableOscilator::setFrequency);
   tableOscilator.def_property("amplitude", &TableOscilator::getAmplitude, &TableOscilator::setAmplitude);
   tableOscilator.def("init", &TableOscilator::init);
   tableOscilator.def("createSound", &TableOscilator::createSound);
   tableOscilator.def_static("frequencyFromCV", &TableOscilator::frequencyFromCV);
}