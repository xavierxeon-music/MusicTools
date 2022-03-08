#include <pybind11/pybind11.h>

#include <Tools/SevenBit.h>

void init_SevenBit(pybind11::module_& module)
{
   auto sevenBit = module.def_submodule("SevenBit");
   sevenBit.def_static("encode", &SevenBit::encode);
   sevenBit.def_static("decode", &SevenBit::decode);
}
