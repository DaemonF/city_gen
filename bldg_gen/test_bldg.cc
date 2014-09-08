#include "polygon.h"
#include <iostream>

using namespace std;

int main()
{
  Polygon polygon(makeRectangle(10, 10, 1));

  cout << "Original rectangle:\n";
  polygon.dumpAscii();
  //cout << polygon << endl;

  polygon.cutAllCorners(2, 2);
  cout << "\nAfter all corner cuts:\n";
  polygon.dumpAscii();
  //cout << polygon << endl;
}
