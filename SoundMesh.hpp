#ifndef SoundMeshHPP
#define SoundMeshHPP

#include <Sound/SoundMesh.h>

#include <Tools/Range.h>

// grid

SoundMesh::Grid::Grid(const uint16_t& size)
   : size(size)
   , data(nullptr)
{
   data = new float[size * size];
}

SoundMesh::Grid::~Grid()
{
   delete[] data;
   data = nullptr;
}

float SoundMesh::Grid::get(const uint16_t& x, const uint16_t& y) const
{
   return data[index(x, y)];
}

void SoundMesh::Grid::set(const uint16_t& x, const uint16_t& y, const float& value)
{
   data[index(x, y)] = value;
}

const uint16_t& SoundMesh::Grid::getSize() const
{
   return size;
}

void SoundMesh::Grid::fill(PointFunction pointFunction)
{
   for (uint16_t x = 0; x < size; x++)
   {
      for (uint16_t y = 0; y < size; y++)
      {
         const float value = pointFunction({x, y});
         set(x, y, value);
      }
   }
}

SoundMesh::Path SoundMesh::Grid::createPath(AngleFunction angleFunction, const uint64_t& noOfSteps)
{
   Path path(noOfSteps, {0, 0});

   Range::Mapper mapper(-1, 1, 0, size - 1);

   const float anglePerStep = 2.0 * Maths::pi / static_cast<float>(noOfSteps);
   for (uint64_t index = 0; index < noOfSteps; index++)
   {
      const float angle = index * anglePerStep;
      const PointF pf = angleFunction(angle);

      const uint16_t x = static_cast<uint16_t>(mapper(pf.x));
      const uint16_t y = static_cast<uint16_t>(mapper(pf.y));

      path[index] = {x, y};
   }

   return path;
}

uint32_t SoundMesh::Grid::index(const uint16_t& x, const uint16_t& y) const
{
   return (x * size) + y;
}

// table

SoundMesh::Table::Table(const uint64_t& noOfSteps)
   : WaveTable::StepTable(noOfSteps)
   , table(nullptr)
{
   table = new float[noOfSteps];
}

SoundMesh::Table::~Table()
{
   delete[] table;
   table = nullptr;
}

void SoundMesh::Table::update(const Grid& grid, const Path& path)
{
   for (uint64_t index = 0; index < noOfSteps; index++)
   {
      const uint16_t x = path[index].xIndex;
      const uint16_t y = path[index].yIndex;
      const float value = grid.get(x, y);
      table[index] = value;
   }
}

float SoundMesh::Table::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return table[index];
}

#endif // NOT SoundMeshHPP
