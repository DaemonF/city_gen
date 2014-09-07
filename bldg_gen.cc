#include "bldg_gen.h"
#include <assert.h>

std::list<Line> makeRectangle(int sizeX, int sizeZ, int y) {
  Pt pt1(0, y, 0);
  Pt pt2(sizeX, y, 0);
  Pt pt3(sizeX, y, sizeZ);
  Pt pt4(0, y, sizeZ);

  std::list<Line> rectangle;
  rectangle.push_back(Line(pt1, pt2));
  rectangle.push_back(Line(pt2, pt3));
  rectangle.push_back(Line(pt3, pt4));
  rectangle.push_back(Line(pt4, pt1));

  return rectangle;
}
