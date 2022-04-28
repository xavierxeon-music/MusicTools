#ifndef SoundMeshH
#define SoundMeshH

#include <functional>

#include <Sound/WaveTable.h>

namespace SoundMesh
{
   struct Point
   {
      uint16_t xIndex;
      uint16_t yIndex;
   };
   using Path = std::vector<Point>;

   class Grid
   {
   public:
      using AngleFunction = std::function<float(const float& valuesPerAngle)>; // give unity radius for given angle
      using PointFunction = std::function<float(const const Point& point)>;
      using Row = float*;

   public:
      inline Grid(const uint16_t& size); // grid is always square
      inline ~Grid();

   public:
      inline Row& operator[](const uint16_t& index);
      inline const uint16_t& getSize() const;

      inline void fill(PointFunction pointFunction);
      inline Path createPath(AngleFunction angleFunction, const uint64_t& noOfSteps); // scales up from unity radius and searches nearest neighbour

   private:
      const uint16_t size;
      Row* data;
   };

   class Table : public WaveTable::StepTable
   {
   public:
      inline Table(const uint64_t& noOfSteps);

   public:
      inline void update(const Grid& grid, const Path& path);
      inline virtual float valueByAngle(const float& angle) const override;

   private:
      float* table;
   };
} // namespace SoundMesh

#ifndef SoundMeshHPP
#include "../../SoundMesh.hpp"
#endif // NOT SoundMeshHPP

#endif // NOT SoundMeshH
