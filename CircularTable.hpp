#ifndef CircularTableHPP
#define CircularTableHPP

#include <Sound/CircularTable.h>

CircularTable::CircularTable(const float maxAngle)
   : maxAngle(maxAngle)
{
}

CircularTable::~CircularTable()
{
}

const float& CircularTable::getMaxAngle() const
{
   return maxAngle;
}

#endif // CircularTableHPP
