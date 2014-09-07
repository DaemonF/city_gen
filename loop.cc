#include "loop.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

std::ostream& operator<<(std::ostream &os, const Pt &pt) {
  return os << "Pt(" << pt.x() << ", " << pt.y() << ", " << pt.z() << ")";
}

std::ostream& operator<<(std::ostream &os, const Line &line) {
  return os << "Line(" << line.start() << ", " << line.end() << ")";
}

std::ostream& operator<<(std::ostream &os, const Loop &loop) {
  // TODO just show points, since we're verified to be valid?
  os << "Loop(\n";
  for (auto line : loop.lines) {
    os << "  " << line << std::endl;
  }
  os << ")";
  return os;
}

Loop::Loop(std::list<Line> initialLines) {
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
    // TODO make an equality checker for points
    assert(l1.end().x() == l2.start().x());
    assert(l1.end().y() == l2.start().y());
    assert(l1.end().z() == l2.start().z());
  }
  // Don't forget to compare the last and first
  Line l1 = lines.back();
  Line l2 = lines.front();
  assert(l1.end().x() == l2.start().x());
  assert(l1.end().y() == l2.start().y());
  assert(l1.end().z() == l2.start().z());
}

void Loop::dumpAscii() const {
  // TODO assume the min is 0

  // Discover the bounds
  int maxX = 0;
  int maxZ = 0;
  // TODO be functional!
  for (auto line : lines) {
    maxX = std::max(maxX, line.start().x());
    maxX = std::max(maxX, line.end().x());

    maxZ = std::max(maxZ, line.start().z());
    maxZ = std::max(maxZ, line.end().z());
  }

  // Fill out a lil grid
  std::vector< std::vector<int> > grid(maxX + 1, std::vector<int>(maxZ + 1));
  // TODO const line& ?
  for (auto line : lines) {
    // TODO this assumes all lines are either horiz/vertical and have same height (all should be
    // true)
    int x1 = line.start().x();
    int z1 = line.start().z();
    int x2 = line.end().x();
    int z2 = line.end().z();
    int y = line.start().y();

    for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
      for (int z = std::min(z1, z2); z <= std::max(z1, z2); z++) {
        grid[x][z] = y;
      }
    }
  }

  // Print, interpreting each z as a row
  for (int z = 0; z <= maxZ; z++) {
    for (int x = 0; x <= maxX; x++) {
      int y = grid[x][z];
      char tile = y == 0 ? ' ' : 'a' + (y - 1);
      std::cout << tile;
    }
    std::cout << std::endl;
  }
}

void Loop::cutFirstCorner(int cutX, int cutZ) {
  assert(cutX >= 0);
  assert(cutZ >= 0);

  auto iter = lines.begin();
  Line l1 = *iter;
  iter++;
  Line l2 = *iter;
  Pt oldSharedVertex = l1.end();

  // Move shared_vert by cutX and cutZ, but pick the direction to wind up inside the loop.
  // TODO depends on some directional stuff making sense... maybe pick the dx, dy multiplier by the
  // two lines, to be flexible?

  int dxLine1 = -l1.getDirectionX() * cutX;
  int dzLine1 = -l1.getDirectionZ() * cutZ;
  int dxLine2 = -l2.getDirectionX() * cutX;
  int dzLine2 = -l2.getDirectionZ() * cutZ;
  // TODO wow, more fluent style, please? :P
  Line newLine1(l1.start(), l1.end().delta(dxLine1, 0, dzLine1));
  Line newLine2(newLine1.end(), newLine1.end().delta(dxLine2, 0, dzLine2));
  Line newLine3(newLine2.end(), newLine2.end().delta(-dxLine1, 0, -dzLine1));
  Line newLine4(newLine3.end(), l2.end());

  // Point to l1 again
  iter--;
  // Goodbye l1
  iter = lines.erase(iter);
  // Goodbye l2
  iter = lines.erase(iter);
  lines.insert(iter, newLine1);
  lines.insert(iter, newLine2);
  lines.insert(iter, newLine3);
  lines.insert(iter, newLine4);

  assertValid();
}
