#include <pybind11/pybind11.h>

#include <Blocks/Trapezoid.h>

void init_Trapezoid(pybind11::module_& module)
{
   pybind11::class_<Trapezoid> tempo(module, "Trapezoid");
   tempo.def(pybind11::init<>());

   tempo.def_static("stageName", &Trapezoid::stageName);

   tempo.def("init", &Trapezoid::init);
   tempo.def("clockTick", &Trapezoid::clockTick);
   tempo.def("clockReset", &Trapezoid::clockReset);

   tempo.def("getCurrentStage", &Trapezoid::getCurrentStage);
   tempo.def("getCurrentStagePercentage", &Trapezoid::getCurrentStagePercentage);
   tempo.def("getCurrentValue", &Trapezoid::getCurrentValue);

   tempo.def("getStageLength", &Trapezoid::getStageLength);
   tempo.def("changeStageLength", &Trapezoid::changeStageLength);

   tempo.def("getStepSize", &Trapezoid::getStepSize);
   tempo.def("changeStepSize", &Trapezoid::changeStepSize);
   tempo.def("getBound", &Trapezoid::getBound);
   tempo.def("changeBound", &Trapezoid::changeBound);
   tempo.def("isValid", &Trapezoid::isValid);

   pybind11::enum_<Trapezoid::Stage> division(tempo, "Stage");
   division.value("Wait", Trapezoid::Stage::Wait);
   division.value("Rise", Trapezoid::Stage::Rise);
   division.value("High", Trapezoid::Stage::High);
   division.value("Fall", Trapezoid::Stage::Fall);
   division.value("Low", Trapezoid::Stage::Low);
   division.export_values();

   pybind11::enum_<Trapezoid::Bound> runState(tempo, "Bound");
   runState.value("Min", Trapezoid::Bound::Min);
   runState.value("Max", Trapezoid::Bound::Max);
   runState.export_values();
}
