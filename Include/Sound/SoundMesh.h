#ifndef SoundMeshH
#define SoundMeshH

#include <functional>

#include <Sound/WaveTable.h>

pyexport namespace SoundMesh
{
   pyexport struct Point
   {
      pyexport uint16_t xIndex;
      pyexport uint16_t yIndex;
   };
   using Path = std::vector<Point>;

   pyexport class Grid
   {
   public:
      pyexport struct PointF
      {
         float x;
         float y;
      };
      using AngleFunction = std::function<PointF(const float& angle)>; // paramatreic eqaution, x & y should be in range [-1, 1]
      using PointFunction = std::function<float(const Point& point)>;  // return should be in range [-1, 1]

   public:
      pyexport inline Grid(const uint16_t& size); // grid is always square
      inline ~Grid();

   public:
      pyexport inline const uint16_t& getSize() const;
      pyexport inline float get(const uint16_t& x, const uint16_t& y) const;
      pyexport inline void set(const uint16_t& x, const uint16_t& y, const float& value);

      inline void fill(PointFunction pointFunction);
      inline Path createPath(AngleFunction angleFunction, const uint64_t& noOfSteps); // scales up from unity radius and searches nearest neighbour

   private:
      uint32_t index(const uint16_t& x, const uint16_t& y) const;

   private:
      const uint16_t size;
      float* data;
   };

   pyexport class Table : public WaveTable::StepTable
   {
   public:
      pyexport inline Table(const uint64_t& noOfSteps);
      inline ~Table();

   public:
      pyexport inline void update(const Grid& grid, const Path& path);
      pyexport inline virtual float valueByAngle(const float& angle) const override;

   private:
      float* table;
   };
} // namespace SoundMesh

#ifndef SoundMeshHPP
#include "../../SoundMesh.hpp"
#endif // NOT SoundMeshHPP

#endif // NOT SoundMeshH
