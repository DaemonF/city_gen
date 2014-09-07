#include "grid.h"
#include "bldg_gen.h"

int main()
{
  Grid grid(10, 10);

  initializeRectangle(grid, 0, 0, 10, 10, 1);
  CutCornerOptions options = {40, 20};
  CutCornerBounds bounds = {0, 10, 0, 10};
  cutCorners(grid, bounds, 0, 1, options);

  grid.dumpAscii();
}
