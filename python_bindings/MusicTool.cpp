#include <pybind11/pybind11.h>

void init_CircularTable(pybind11::module_& module);
void init_TableOscilator(pybind11::module_& module);
void init_StandardTable(pybind11::module_& module);

void init_Note(pybind11::module_& module);
void init_Tempo(pybind11::module_& module);

void init_Range(pybind11::module_& module);
void init_FastRandom(pybind11::module_& module);

PYBIND11_MODULE(_xxmodularsynth, module)
{
   init_CircularTable(module);
   init_TableOscilator(module);
   init_StandardTable(module);

   init_Note(module);
   init_Tempo(module);

   init_Range(module);
   init_FastRandom(module);
}
