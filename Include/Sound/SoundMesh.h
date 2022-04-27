#ifndef SoundMeshH
#define SoundMeshH

#include <functional>

#include <Sound/WaveTableMorpher.h>

// Sound  Mesh is namespace

// PathTable

// Grid
// * PathTable applyPath

class SoundMesh
{
public:
   struct Point
   {
      uint16_t xIndex;
      uint16_t yIndex;
   };

   class Grid
   {
   public:
      Grid(const uint16_t xSize, const uint16_t ySize);
   };

   using Path = std::vector<Point>;

   using PointFunction = std::function<float(const Point& point)>;
   using AngleFunction = std::function<Point(const float& valuesPerAngle)>;

public:
   inline SoundMesh();

public:
   inline void setGrid(const Grid& newGrid);
   inline void createAndSetGrid(PointFunction pointFunction, const uint16_t xSize, const uint16_t ySize);

   inline WaveTable::StepTable applyPath(const Path& newPath);
   inline WaveTable::StepTable createAndApplyPath(AngleFunction angleFunction, const uint16_t noOfElements);

private:
   Grid grid;
};

#ifndef SoundMeshHPP
#include "../../SoundMesh.hpp"
#endif // NOT SoundMeshHPP

#endif // NOT SoundMeshH
