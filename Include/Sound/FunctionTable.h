#ifndef FunctionTableH
#define FunctionTableH

#include <Sound/WaveTable.h>

#include <functional>

class FunctionTable : public WaveTable::StepTable
{
public:
   using AngleFunction = std::function<float(const float& valuesPerAngle)>;

public:
   inline FunctionTable(AngleFunction angleFunction, const uint64_t& noOfSteps, const float maxAngle = 2.0f * Maths::pi);
   inline ~FunctionTable();

public:
   inline virtual float valueByAngle(const float& angle) const override;

protected:
   float* table;
};

#ifndef FunctionTableHPP
#include "../../FunctionTable.hpp"
#endif // NOT FunctionTableHPP

#endif // NOT FunctionTableH
