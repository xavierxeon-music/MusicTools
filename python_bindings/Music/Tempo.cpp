#include <pybind11/pybind11.h>

#include <Music/Tempo.h>

void init_Tempo(pybind11::module_& module)
{
   pybind11::class_<Tempo> tempo(module, "Tempo");
   tempo.def(pybind11::init<>());
   tempo.def_static("getName", &Tempo::getName);
   tempo.def("getRunState", &Tempo::getRunState);
   tempo.def("isRunningOrFirstTick", &Tempo::isRunningOrFirstTick);
   tempo.def("getCounter", &Tempo::getCounter);
   tempo.def("getPercentage", &Tempo::getPercentage);
   tempo.def("getBeatsPerMinute", &Tempo::getBeatsPerMinute);
   tempo.def("advance", &Tempo::advance);
   tempo.def("clockTick", &Tempo::clockTick);
   tempo.def("clockReset", &Tempo::clockReset);

   pybind11::enum_<Tempo::Division> division(tempo, "Division");
   division.value("Sixteenth", Tempo::Division::Sixteenth);
   division.value("Eigth", Tempo::Division::Eigth);
   division.value("Quarter", Tempo::Division::Quarter);
   division.value("Bar", Tempo::Division::Bar);
   division.export_values();

   pybind11::enum_<Tempo::RunState> runState(tempo, "RunState");
   runState.value("Reset", Tempo::RunState::Reset);
   runState.value("Off", Tempo::RunState::Off);
   runState.value("FirstTick", Tempo::RunState::FirstTick);
   runState.value("Running", Tempo::RunState::Running);
   runState.export_values();
}
