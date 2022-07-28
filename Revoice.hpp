#ifndef RevoiceHPP
#define RevoiceHPP

#include <Effect/Revoice.h>

Revoice::Revoice()
   : Abstract::BufferedEffect(Spectrum::compileBufferSize())
   , spectrum()
{
}

Data Revoice::proccessBuffer(const Data& input)
{
}

#endif // NOT RevoiceHPP
