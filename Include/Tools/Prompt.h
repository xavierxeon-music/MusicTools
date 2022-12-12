#ifndef PromptH
#define PromptH

class Prompt
{
public:
   inline Prompt();

public:
   inline void arm();
   inline bool reset(); // true if it was armed

private:
   bool active;
};

#ifndef PromptHPP
#include "../../Prompt.hpp"
#endif // NOT PromptHPP

#endif // NOT PromptH
