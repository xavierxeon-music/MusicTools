#include <pybind11/pybind11.h>

// Blocks
void init_Trapezoid(pybind11::module_& module);

// Music
void init_Note(pybind11::module_& module);
void init_Tempo(pybind11::module_& module);

// Sound
void init_CircularTable(pybind11::module_& module);
void init_TableOscilator(pybind11::module_& module);
void init_StandardTable(pybind11::module_& module);

// Tools
void init_FastRandom(pybind11::module_& module);
void init_Range(pybind11::module_& module);
void init_SevenBit(pybind11::module_& module);

PYBIND11_MODULE(_xxmodularsynth, module)
{
   //Blocks
   init_Trapezoid(module);

   // Music
   init_Note(module);
   init_Tempo(module);

   // Sound
   init_CircularTable(module);
   init_TableOscilator(module);
   init_StandardTable(module);

   // Tools
   init_FastRandom(module);
   init_Range(module);
   init_SevenBit(module)
}
