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

void cutCorners(
  Grid &grid, const CutCornerBounds& bounds, int lowerY, int borderY,
  const CutCornerOptions &options
) {
  assert(lowerY < borderY);

  int sizeX = bounds.x2 - bounds.x1;
  int sizeZ = bounds.z2 - bounds.z1;
  int x1 = bounds.x1;
  int x2 = bounds.x2 - 1;
  int z1 = bounds.z1;
  int z2 = bounds.z2 - 1;

  int cutX = sizeX * options.percentX / 100;
  int cutZ = sizeZ * options.percentZ / 100;

  // top-left
  // TODO make fill first check that the value below is something known
  // First fill the big blob with the border, then do a slightly smaller one with the lower height
  fill(grid, x1, x1 + cutX, z1, z1 + cutZ, borderY);
  // TODO watch out when we slice '1'
  fill(grid, x1, x1 + cutX - 1, z1, z1 + cutZ - 1, lowerY);
}
