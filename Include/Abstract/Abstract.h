#ifndef AbstractH
#define AbstractH

#include <Global.h>

enum class Encoder
{
   None,
   Forwad,
   Back,
   Clicked,
   LongPressed
};

struct Input
{
   float knobs[4] = {0.0, 0.0, 0.0, 0.0};
   bool gates[2] = {false, false};
};

struct Output
{
   float cvs[2] = {0.0, 0.0};
   bool gate = false;
   bool led = false;
};

enum class Alignment
{
   Left,
   Center,
   Right
};

#endif // AbstractH
