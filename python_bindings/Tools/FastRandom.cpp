#include <pybind11/pybind11.h>

#include <Tools/FastRandom.h>

void init_FastRandom(pybind11::module_& module)
{
   pybind11::class_<FastRandom> fastRandom(module, "FastRandom");
   fastRandom.def(pybind11::init<const uint64_t&>());
   fastRandom.def("reset", &FastRandom::reset);
   fastRandom.def("skip", &FastRandom::skip);
   fastRandom.def("value", &FastRandom::value);
}
