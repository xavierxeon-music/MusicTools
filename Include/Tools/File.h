#ifndef FileH
#define FileH

#include <MusicTools.h>

struct File
{
   inline static bool exists(const std::string& fileName);
   inline static Bytes load(const std::string& fileName);
   inline static void save(const Bytes& data, const std::string& fileName);
   inline static long getLasModifiedTimeStamp(const std::string& fileName);
};

#ifndef FileHPP
#include "../../File.hpp"
#endif // NOT FileHPP

#endif // NOT FileH
