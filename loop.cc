#include "loop.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

Loop::Loop(std::list<Line> initialLines) {
  // TODO copy better?
  for (auto line : initialLines) {
    lines.push_back(line);
  }
}

void Loop::assertValid() {
  auto iter = lines.begin();
  while (iter != lines.end()) {
    Line l1 = *iter;
    iter++;
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
