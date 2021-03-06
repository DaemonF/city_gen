#include "polygon.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

ostream& operator<<(ostream &os, const Pt &pt) {
  return os << "Pt(" << pt.x() << ", " << pt.z() << ")";
}

ostream& operator<<(ostream &os, const Line &line) {
  return os << "Line(" << line.start() << ", " << line.end() << ")";
}

ostream& operator<<(ostream &os, const Polygon &polygon) {
  os << "Polygon(\n";
  for (auto pt : polygon.points) {
    os << "  " << pt << endl;
  }
  os << ")";
  return os;
}

// TODO const &?
bool operator==(Pt pt1, Pt pt2) {
  return pt1.x() == pt2.x() && pt1.z() == pt2.z();
}
bool operator!=(Pt pt1, Pt pt2) {
  return !(pt1 == pt2);
}

Polygon::Polygon(list<Pt> initialPoints, int height) {
  y = height;
  // TODO copy better?
  for (auto pt : initialPoints) {
    points.push_back(pt);
  }
}

list<Line> Polygon::getLines() const {
  list<Line> lines;
  for (auto iter = points.begin(); iter != points.end(); iter++) {
    if (next(iter) != points.end()) {
      lines.push_back(Line(*iter, *next(iter)));
    } else {
      lines.push_back(Line(*iter, points.front()));
    }
  }
  return lines;
}

list<Pt> makeRectangle(int sizeX, int sizeZ) {
  list<Pt> rectangle;
  rectangle.push_back(Pt(0, 0));
  rectangle.push_back(Pt(sizeX, 0));
  rectangle.push_back(Pt(sizeX, sizeZ));
  rectangle.push_back(Pt(0, sizeZ));
  return rectangle;
}

list<Pt> cutCorner(Pt pt1, Pt pt2, Pt pt3, int cutX, int cutZ) {
  assert(cutX >= 0);
  assert(cutZ >= 0);

  // Move pt2 by cutX and cutZ, but pick the direction to wind up inside the polygon.
  Line l1(pt1, pt2);
  Line l2(pt2, pt3);
  int dxLine1 = -l1.getDirectionX() * cutX;
  int dzLine1 = -l1.getDirectionZ() * cutZ;
  int dxLine2 = l2.getDirectionX() * cutX;
  int dzLine2 = l2.getDirectionZ() * cutZ;
  //cout << "deltas: " << dxLine1 << ", " << dzLine1 << " and " << dxLine2 << ", " << dzLine2 << endl;

  list<Pt> result;
  result.push_back(pt2.delta(dxLine1, dzLine1));
  result.push_back(pt2.delta(dxLine1 + dxLine2, dzLine1 + dzLine2));
  result.push_back(pt2.delta(dxLine2, dzLine2));

  return result;
}

void Polygon::cutAllCorners(int cutX, int cutZ) {
  list<Pt> result;

  Pt pt1 = points.front();
  auto iter = next(points.begin());
  Pt pt2 = *iter;
  Pt pt3 = *next(iter);

  while (true) {
    auto newPoints = cutCorner(pt1, pt2, pt3, cutX, cutZ);
    result.insert(result.end(), newPoints.begin(), newPoints.end());

    iter++;
    if (iter == points.end()) {
      break;
    }
    pt1 = result.back();
    if (next(iter) == points.end()) {
      pt2 = *iter;
      // NOT result.front(), because that's been shifted!
      pt3 = points.front();
    } else {
      pt2 = *iter;
      pt3 = *next(iter);
    }
  }

  // The wrap-around case
  auto lastPoints = cutCorner(result.back(), points.front(), result.front(), cutX, cutZ);
  result.insert(result.end(), lastPoints.begin(), lastPoints.end());

  points.clear();
  points.swap(result);
}
