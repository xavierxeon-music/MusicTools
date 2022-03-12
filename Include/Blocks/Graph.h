#ifndef GraphH
#define GraphH

#include <Remember.h>

#include <Music/Tempo.h>
#include <Tools/Counter.h>

class Graph : public Remember::Container
{
public:
   class Point : public Remember::Container
   {
   public:
      inline Point();

   private:
      using Height_ = Remember::Value<uint8_t>;
      using Length_ = Remember::Value<uint8_t>;

   private:
      Height_ height;
      Length_ length;
   };

public:
   inline Graph();

public:
   inline void init();
   inline void clockTick();
   inline void clockReset();

   inline Tempo::Division getStepSize() const;
   inline void changeStepSize(bool longer);

   inline bool isValid() const;

private:
   using StepSize_ = Remember::Value<Tempo::Division>;
   using PointList_ = Remember::RefList<Point>;

private:
   StepSize_ stepSize;
   PointList_ pointList;

   uint64_t currentPointIndex;
   Counter stepSizeCounter;
   Counter stageLengthCounter;
   bool firstTickDone;
};

#include "Graph.hpp"

#endif // GraphH
