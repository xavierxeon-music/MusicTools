#ifndef FunctionTableH
#define FunctionTableH

#include <Sound/WaveTable.h>

#include <functional>

class FunctionTable : public WaveTable::StepValueTable
{
public:
   using AngleFunction = std::function<float(const float& valuesPerAngle)>;

public:
   inline FunctionTable(AngleFunction angleFunction, const uint64_t& noOfSteps, const float maxAngle = 2.0f * Maths::pi);   
};

#ifndef FunctionTableHPP
#include "../../FunctionTable.hpp"
#endif // NOT FunctionTableHPP

#endif // NOT FunctionTableH
