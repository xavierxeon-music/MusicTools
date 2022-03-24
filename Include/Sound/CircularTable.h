#ifndef CircularTableH
#define CircularTableH

#include <functional>

#include <Maths.h>
#include <MusicTools.h>

// a table used in a TableOscilator

class CircularTable
{
public:
   inline CircularTable(const float maxAngle = 2.0f * Maths::pi);
   inline virtual ~CircularTable();

public:
   inline const float& getMaxAngle() const;
   inline virtual float valueByAngle(const float& angle) const = 0;

protected:
   const float maxAngle;
};

#ifndef CircularTableHPP
#include "../../CircularTable.hpp"
#endif // NOT CircularTableHPP

#endif // NOT CircularTableH
