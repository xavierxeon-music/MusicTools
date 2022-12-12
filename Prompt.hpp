#ifndef PromptHPP
#define PromptHPP

#include <Tools/Prompt.h>

Prompt::Prompt()
   : active(false)
{
}

void Prompt::arm()
{
   active = true;
}

bool Prompt::reset()
{
   if (!active)
      return false;

   active = false;
   return true;
}

#endif // NOT PromptHPP
