#include "loop.h"
#include <iostream>

using namespace std;

int main()
{
  Loop loop(makeRectangle(10, 10, 1));

  cout << "Original rectangle:\n";
  loop.dumpAscii();
  //cout << loop << endl;

  loop.cutAllCorners(2, 2);
  cout << "\nAfter all corner cuts:\n";
  loop.dumpAscii();
  //cout << loop << endl;
}
