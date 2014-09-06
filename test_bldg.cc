#include "grid.h"
#include "bldg_gen.h"

int main()
{
  Grid grid(10, 10);
  initializeRectangle(grid, 0, 0, 10, 10, 1);
  grid.dumpAscii();
}
