#ifndef SoundMeshH
#define SoundMeshH

#include <Sound/TableMorpher.h>

class SoundMesh : public TableMorpher
{
public:
   struct Point
   {
      uint16_t xIndex;
      uint16_t yIndex;
   };

   using Path = std::vector<Point>;

public:
   inline SoundMesh();

public:
   inline bool step() override;
   inline void init(const uint16_t& newGridSize);
   inline void setPath(const Path& newPath);

private:
   using TableMorpher::addTable;
   using TableMorpher::setLoop;
   using TableMorpher::setMix;

private:
   uint16_t gridSize;
   Path path;
};

#ifndef SoundMeshHPP
#include "../../SoundMesh.hpp"
#endif // NOT SoundMeshHPP

#endif // NOT SoundMeshH
