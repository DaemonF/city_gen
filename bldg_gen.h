#include "grid.h"

// Fill [x1, x2] and [z1, z2] inclusively with targetY
void fill(Grid &grid, int x1, int x2, int z1, int z2, int targetY);
// size is interpreted exclusively
void initializeRectangle(Grid &grid, int atX, int atZ, int sizeX, int sizeZ, int targetY);
