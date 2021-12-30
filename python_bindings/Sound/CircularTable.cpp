#include <pybind11/pybind11.h>

#include <Sound/CircularTable.h>

class PyCircularTable : public CircularTable
{
   using CircularTable::CircularTable;

   float valueByAngle(const float& angle) const override
   {
      PYBIND11_OVERRIDE_PURE(
         float,         // Return type
         CircularTable, // Parent class
         valueByAngle,  // Name of function in C++ (must match Python name)
         angle          // Argument(s)
      );
   }
};

void init_CircularTable(pybind11::module_& module)
{
   pybind11::class_<CircularTable, PyCircularTable> circularTable(module, "CircularTable");
   circularTable.def(pybind11::init<const float>(), pybind11::arg("maxAngle") = 2.0f * Maths::pi);
   circularTable.def("getMaxAngle", &CircularTable::getMaxAngle);
   circularTable.def("valueByAngle", &CircularTable::valueByAngle);
}