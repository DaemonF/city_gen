#include "grid.h"
#include <assert.h>
#include <iostream>

Grid::Grid(int x, int z) {
  assert(x > 0);
  assert(z > 0);

  dimX = x;
  dimZ = z;
  // TODO really? at least do it using awesome new c++11 stuff?
  tiles.resize(dimX);
  for (int x = 0; x < dimX; x++) {
    tiles[x].resize(dimZ);
  }
}

bool Grid::inBounds(int x, int z) const {
  return (x >= 0 && x < getDimX()) && (z >= 0 && z < getDimZ());
}

int Grid::getDimX() const {
  return dimX;
}

int Grid::getDimZ() const {
  return dimZ;
}

int Grid::get(int x, int z) const {
  assert(inBounds(x, z));

  return tiles[x][z];
}

void Grid::set(int x, int z, int targetY) {
  assert(inBounds(x, z));
  assert(targetY >= 0);

  tiles[x][z] = targetY;
}

void Grid::dumpAscii() const {
  for (int x = 0; x < getDimX(); x++) {
    for (int z = 0; z < getDimZ(); z++) {
      int y = get(x, z);
      if (y == 0) {
        std::cout << '.';
      } else {
        // TODO how to display many levels?
        assert(y < 10);
        std::cout << y;
      }
    }
    std::cout << std::endl;
  }
}
