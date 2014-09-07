#include "loop.h"
#include "bldg_gen.h"
#include <iostream>

int main()
{
  Loop loop(makeRectangle(10, 10, 1));

  std::cout << "Original rectangle:\n";
  loop.dumpAscii();
}
