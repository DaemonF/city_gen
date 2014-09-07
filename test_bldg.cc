#include "loop.h"
#include <iostream>

using namespace std;

int main()
{
  Loop loop(makeRectangle(10, 10, 1));

  cout << "Original rectangle:\n";
  loop.dumpAscii();
  cout << loop << endl;

  loop.cutFirstCorner(4, 3);
  cout << "\nFirst corner cut:\n";
  loop.dumpAscii();
  cout << loop << endl;
}
