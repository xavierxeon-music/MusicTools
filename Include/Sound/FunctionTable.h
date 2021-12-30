#ifndef FunctionTableH
#define FunctionTableH

#include <Sound/CircularTable.h>

#include <functional>

class FunctionTable : public CircularTable
{
public:
   using AngleFunction = std::function<float(const float&)>; // value per angle

public:
   inline FunctionTable(uint64_t resolution, const float maxAngle = 2.0f * Maths::pi);
   inline FunctionTable(uint64_t resolution, AngleFunction angleFunction, const float maxAngle = 2.0f * Maths::pi);

public:
   inline virtual float valueByAngle(const float& angle) const override;
   inline const uint64_t& getResolution() const;

protected:
   inline uint64_t getIndexFromAngle(float angle) const;

protected:
   const uint64_t resolution;
   const float anglePerStep;
   float* table;
};

#include <FunctionTable.hpp>

#endif //  FunctionTableH
