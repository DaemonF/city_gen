#include "grid.h"

int main()
{
  Grid grid(10, 10);
  int floor1 = 1;
  grid.set(0, 0, floor1);
  grid.set(1, 0, floor1);
  grid.set(2, 0, floor1);
  grid.set(3, 0, floor1);
  grid.set(2, 1, floor1);
  //grid.set(10, 0, floor1);  // error
  grid.dumpAscii();
}
