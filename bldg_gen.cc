#include "bldg_gen.h"
#include <assert.h>

void fill(Grid &grid, int x1, int x2, int z1, int z2, int targetY) {
  // TODO rely on underlying grid.set() to assert in-boundedness and such
  assert(x1 <= x2);
  assert(z1 <= z2);

  for (int x = x1; x <= x2; x++) {
    for (int z = z1; z <= z2; z++) {
      grid.set(x, z, targetY);
    }
  }
}

void initializeRectangle(Grid &grid, int atX, int atZ, int sizeX, int sizeZ, int targetY) {
  int left = atX;
  int right = atX + sizeX - 1;
  int top = atZ;
  int bottom = atZ + sizeZ - 1;

  // top row
  fill(grid, left, right, top, top, targetY);
  // bottom row
  fill(grid, left, right, bottom, bottom, targetY);
  // left column
  fill(grid, left, left, top, bottom, targetY);
  // right column
  fill(grid, right, right, top, bottom, targetY);
}
