#ifndef SoundMeshHPP
#define SoundMeshHPP

#include <Sound/SoundMesh.h>

// grid

SoundMesh::Grid::Grid(const uint16_t& size)
   : size(size)
   , data(nullptr)
{
   data = new Row[size];
   for (uint16_t index = 0; index < size; index++)
      data[index] = new float[index];
}

SoundMesh::Grid::~Grid()
{
   for (uint16_t index = 0; index < size; index++)
      delete[] data[index];

   delete[] data;
   data = nullptr;
}

SoundMesh::Grid::Row& SoundMesh::Grid::operator[](const uint16_t& index)
{
   return data[index];
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
         data[x][y] = value;
      }
   }
}

SoundMesh::Path SoundMesh::Grid::createPath(AngleFunction angleFunction, const uint64_t& noOfSteps)
{
   Path path(noOfSteps, {0, 0});

   const float anglePerStep = 2.0 * Maths::pi / static_cast<float>(noOfSteps);
   for (uint64_t index = 0; index < noOfSteps; index++)
   {
      const float angle = index * anglePerStep;
      const PointF pf = angleFunction(angle);
   }

   return path;
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
      const float angle = index * anglePerStep;
      const float value = 0.0;
      table[index] = value;
   }
}

float SoundMesh::Table::valueByAngle(const float& angle) const
{
   const uint64_t index = stepIndexFromAngle(angle);
   return table[index];
}

#endif // NOT SoundMeshHPP
