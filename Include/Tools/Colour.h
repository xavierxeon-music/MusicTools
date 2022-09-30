#ifndef ColorH
#define ColorH

#include <map>

#include <Music/Note.h>
#include <MusicTools.h>

struct Colour
{
   uint8_t red;
   uint8_t green;
   uint8_t blue;

   using NoteMap = std::map<Note::Value, Colour>;
   static const NoteMap noteMap;
};

#endif // NOT ColorH
