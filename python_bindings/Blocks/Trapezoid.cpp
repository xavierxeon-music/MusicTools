#include <pybind11/pybind11.h>

#include <Blocks/Trapezoid.h>

void init_Trapezoid(pybind11::module_& module)
{
   pybind11::class_<Trapezoid> tempo(module, "Trapezoid");
   tempo.def(pybind11::init<>());
   tempo.def_static("stageName", &Trapezoid::stageName);
   tempo.def("init", &Tempo::init);
   tempo.def("clockTick", &Tempo::clockTick);
   tempo.def("clockReset", &Tempo::clockReset);
   tempo.def("getCurrentStage", &Tempo::getCurrentStage);
   tempo.def("getLength", &Tempo::getLength);
   tempo.def("changeLength", &Tempo::changeLength);
   tempo.def("getCurrentStagePercentage", &Tempo::clockTick);
   tempo.def("getCurrentValues", &Tempo::clockReset);
   tempo.def("getStepSize", &Tempo::clockTick);
   tempo.def("changeStepSize", &Tempo::clockReset);
   tempo.def("getBound", &Tempo::clockTick);
   tempo.def("changeBound", &Tempo::clockReset);
   tempo.def("isValid", &Tempo::clockTick);

   pybind11::enum_<Trapezoid::Stage> division(tempo, "Stage");
   division.value("Wait", Trapezoid::Stage::Wait);
   division.value("Rise", Trapezoid::Stage::Rise);
   division.value("High", Trapezoid::Stage::High);
   division.value("Fall", Trapezoid::Stage::Fall);
   division.value("Low", Trapezoid::Stage::Low);
   division.export_values();

   pybind11::enum_<Trapezoid::Bound> runState(tempo, "Bound");
   runState.value("Min", Tempo::Bound::Min);
   runState.value("Max", Tempo::Bound::Max);
   runState.export_values();
}
