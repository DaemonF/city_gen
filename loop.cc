#include "loop.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

ostream& operator<<(ostream &os, const Pt &pt) {
  return os << "Pt(" << pt.x() << ", " << pt.y() << ", " << pt.z() << ")";
}

ostream& operator<<(ostream &os, const Line &line) {
  return os << "Line(" << line.start() << ", " << line.end() << ")";
}

ostream& operator<<(ostream &os, const Loop &loop) {
  // TODO just show points, since we're verified to be valid?
  os << "Loop(\n";
  for (auto line : loop.lines) {
    os << "  " << line << endl;
  }
  os << ")";
  return os;
}

// TODO const &?
bool operator==(Pt pt1, Pt pt2) {
  return pt1.x() == pt2.x() && pt1.y() == pt2.y();
}
bool operator!=(Pt pt1, Pt pt2) {
  return !(pt1 == pt2);
}

Loop::Loop(list<Line> initialLines) {
  // TODO copy better?
  for (auto line : initialLines) {
    lines.push_back(line);
  }

  assertValid();
}

void Loop::assertValid() {
  auto iter = lines.begin();
  while (true) {
    // TODO could also use boost::next()
    Line l1 = *iter;
    iter++;
    if (iter == lines.end()) {
      break;
    }
    Line l2 = *iter;
    assert(l1.end() == l2.start());
  }
  // Don't forget to compare the last and first
  assert(lines.back().end() == lines.front().start());
}

void Loop::dumpAscii() const {
  // TODO assume the min is 0

  // Discover the bounds
  int maxX = 0;
  int maxZ = 0;
  // TODO be functional!
  for (auto line : lines) {
    maxX = max(maxX, line.start().x());
    maxX = max(maxX, line.end().x());

    maxZ = max(maxZ, line.start().z());
    maxZ = max(maxZ, line.end().z());
  }

  // Fill out a lil grid
  vector< vector<int> > grid(maxX + 1, vector<int>(maxZ + 1));
  // TODO const line& ?
  for (auto line : lines) {
    // TODO this assumes all lines are either horiz/vertical and have same height (all should be
    // true)
    int x1 = line.start().x();
    int z1 = line.start().z();
    int x2 = line.end().x();
    int z2 = line.end().z();
    int y = line.start().y();

    for (int x = min(x1, x2); x <= max(x1, x2); x++) {
      for (int z = min(z1, z2); z <= max(z1, z2); z++) {
        grid[x][z] = y;
      }
    }
  }

  // Print, interpreting each z as a row
  for (int z = 0; z <= maxZ; z++) {
    for (int x = 0; x <= maxX; x++) {
      int y = grid[x][z];
      char tile = y == 0 ? ' ' : 'a' + (y - 1);
      cout << tile;
    }
    cout << endl;
  }
}

list<Line> makeRectangle(int sizeX, int sizeZ, int y) {
  Pt pt1(0, y, 0);
  Pt pt2(sizeX, y, 0);
  Pt pt3(sizeX, y, sizeZ);
  Pt pt4(0, y, sizeZ);

  list<Line> rectangle;
  rectangle.push_back(Line(pt1, pt2));
  rectangle.push_back(Line(pt2, pt3));
  rectangle.push_back(Line(pt3, pt4));
  rectangle.push_back(Line(pt4, pt1));

  return rectangle;
}

list<Line> cutCorner(Line l1, Line l2, int cutX, int cutZ) {
  assert(cutX >= 0);
  assert(cutZ >= 0);
  assert(l1.end() == l2.start());

  int dxLine1 = -l1.getDirectionX() * cutX;
  int dzLine1 = -l1.getDirectionZ() * cutZ;
  int dxLine2 = l2.getDirectionX() * cutX;
  int dzLine2 = l2.getDirectionZ() * cutZ;
  //cout << "deltas: " << dxLine1 << ", " << dzLine1 << " and " << dxLine2 << ", " << dzLine2 << endl;
  // TODO wow, more fluent style, please? :P
  Line newLine1(l1.start(), l1.end().delta(dxLine1, 0, dzLine1));
  Line newLine2(newLine1.end(), newLine1.end().delta(dxLine2, 0, dzLine2));
  Line newLine3(newLine2.end(), newLine2.end().delta(-dxLine1, 0, -dzLine1));
  Line newLine4(newLine3.end(), l2.end());

  list<Line> result;
  result.push_back(newLine1);
  result.push_back(newLine2);
  result.push_back(newLine3);
  result.push_back(newLine4);
  return result;
}

void Loop::cutAllCorners(int cutX, int cutZ) {
  list<Line> result;

  lines.zipWith(lines.tail)

  // TODO consider a polygon class with an iterator that makes sense

  auto iter = lines.begin();
  Line l1 = *iter;
  Line l2 = *next(iter);
  while (true) {
    auto newLines = cutCorner(l1, l2, cutX, cutZ);
    // Just append the new lines for now
    result.insert(result.end(), newLines.begin(), newLines.end());

    if (iter == lines.end()) {
      break;
    }
    l1 = newLines.back();
    iter++;
    if (iter == lines.end()) {
      l2 = result.front();
      // TODO have to do special work to stitch it together :(
    }
  }



  Line l1 = *lines.begin()

  auto iter = lines.begin();
  Line l2 = *next(iter);
  while (iter != lines.end()) {


    iter1++;
  }


  //cout << "\nAfter another corner cut:\n";
  //dumpAscii();

  lines.clear();
  lines.swap(result);
  cout << *this << endl;
  assertValid();
}
