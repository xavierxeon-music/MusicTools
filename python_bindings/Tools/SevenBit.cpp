#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Tools/SevenBit.h>

void init_SevenBit(pybind11::module_& module)
{
   pybind11::class_<SevenBit> sevenBit(module, "SevenBit");
   sevenBit.def_static("encode", &SevenBit::encode);
   sevenBit.def_static("decode", &SevenBit::decode);
}
