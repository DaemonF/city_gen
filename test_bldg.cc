#include "loop.h"
#include "bldg_gen.h"
#include <iostream>

int main()
{
  Loop loop(makeRectangle(10, 10, 1));

  std::cout << "Original rectangle:\n";
  loop.dumpAscii();

  loop.cutFirstCorner(4, 3);
  std::cout << "\nFirst corner cut:\n";
  loop.dumpAscii();
}
