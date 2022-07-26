#include <pybind11/pybind11.h>

#include <Blocks/PolyRamp.h>

void init_PolyRamp(pybind11::module_& module)
{
   pybind11::class_<PolyRamp> polyRamp(module, "PolyRamp");
   polyRamp.def(pybind11::init<>());

   pybind11::enum_<PolyRamp::LengthStatus> lengthStatus(polyRamp, "LengthStatus");
   lengthStatus.value("Kept", PolyRamp::LengthStatus::Kept);
   lengthStatus.value("Changed", PolyRamp::LengthStatus::Changed);
   lengthStatus.value("Error", PolyRamp::LengthStatus::Error);
   lengthStatus.export_values();

   polyRamp.def("clear", &PolyRamp::clear);

   polyRamp.def("clockTick", &PolyRamp::clockTick);
   polyRamp.def("clockReset", &PolyRamp::clockReset);

   polyRamp.def("getCurrentStageIndex", &PolyRamp::getCurrentStageIndex);
   polyRamp.def("getCurrentStagePercentage", &PolyRamp::getCurrentStagePercentage);
   polyRamp.def("getCurrentValue", &PolyRamp::getCurrentValue);

   polyRamp.def("isValid", &PolyRamp::isValid);

   polyRamp.def("getStepSize", &PolyRamp::getStepSize);
   polyRamp.def("setStepSize", &PolyRamp::setStepSize);
   polyRamp.def("changeStepSize", &PolyRamp::changeStepSize);

   polyRamp.def("getLength", &PolyRamp::getLength);
   polyRamp.def("setLength", &PolyRamp::setLength);
   polyRamp.def("trimLength", &PolyRamp::trimLength);

   polyRamp.def("getStageCount", &PolyRamp::getStageCount);
   polyRamp.def("addStage", &PolyRamp::addStage);
   polyRamp.def("moveStage", &PolyRamp::moveStage);
   polyRamp.def("removeStage", &PolyRamp::removeStage);

   polyRamp.def("getStageStartHeight", &PolyRamp::getStageStartHeight);
   polyRamp.def("setStageStartHeight", &PolyRamp::setStageStartHeight);

   polyRamp.def("getStageEndHeight", &PolyRamp::getStageEndHeight);
   polyRamp.def("setStageEndHeight", &PolyRamp::setStageEndHeight);

   polyRamp.def("getStageLength", &PolyRamp::getStageLength);
   polyRamp.def("setStageLength", &PolyRamp::setStageLength);

   polyRamp.def("isLooping", &PolyRamp::isLooping);
   polyRamp.def("setLooping", &PolyRamp::setLooping);
}