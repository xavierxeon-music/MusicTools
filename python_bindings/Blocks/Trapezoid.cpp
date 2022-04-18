#include <pybind11/pybind11.h>

#include <Blocks/Trapezoid.h>

void init_Trapezoid(pybind11::module_& module)
{
   pybind11::class_<Trapezoid> trapezoid(module, "Trapezoid");
   trapezoid.def(pybind11::init<>());

   trapezoid.def_static("stageName", &Trapezoid::stageName);

   trapezoid.def("init", &Trapezoid::init);
   trapezoid.def("clockTick", &Trapezoid::clockTick);
   trapezoid.def("clockReset", &Trapezoid::clockReset);

   trapezoid.def("getCurrentStage", &Trapezoid::getCurrentStage);
   trapezoid.def("getCurrentStagePercentage", &Trapezoid::getCurrentStagePercentage);
   trapezoid.def("getCurrentValue", &Trapezoid::getCurrentValue);

   trapezoid.def("getStageLength", &Trapezoid::getStageLength);
   trapezoid.def("changeStageLength", &Trapezoid::changeStageLength);

   trapezoid.def("getStepSize", &Trapezoid::getStepSize);
   trapezoid.def("changeStepSize", &Trapezoid::changeStepSize);
   trapezoid.def("getBound", &Trapezoid::getBound);
   trapezoid.def("changeBound", &Trapezoid::changeBound);
   trapezoid.def("isValid", &Trapezoid::isValid);

   pybind11::enum_<Trapezoid::Stage> division(trapezoid, "Stage");
   division.value("Wait", Trapezoid::Stage::Wait);
   division.value("Rise", Trapezoid::Stage::Rise);
   division.value("High", Trapezoid::Stage::High);
   division.value("Fall", Trapezoid::Stage::Fall);
   division.value("Low", Trapezoid::Stage::Low);
   division.export_values();

   pybind11::enum_<Trapezoid::Bound> runState(trapezoid, "Bound");
   runState.value("Min", Trapezoid::Bound::Min);
   runState.value("Max", Trapezoid::Bound::Max);
   runState.export_values();
}
