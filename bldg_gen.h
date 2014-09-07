#include "grid.h"

// Fill [x1, x2] and [z1, z2] inclusively with targetY
void fill(Grid &grid, int x1, int x2, int z1, int z2, int targetY);
// size is interpreted exclusively
void initializeRectangle(Grid &grid, int atX, int atZ, int sizeX, int sizeZ, int targetY);

struct CutCornerOptions {
  // TODO have min/max percents
  // TODO have chance to cut a corner at all
  int percentX, percentZ;  // [0, 100]
};
// Specify the source rectangle
struct CutCornerBounds {
  int x1, x2, z1, z2;
};
// lowerY is beneath the border
void cutCorners(
  Grid &grid, const CutCornerBounds& bounds, int lowerY, int borderY,
  const CutCornerOptions &options
);
