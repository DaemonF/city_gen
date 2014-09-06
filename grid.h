#pragma once
#include <vector>

// TODO most of this stuff should be private to the generation/grid part of the code

/**
 * Coordinate system notes:
 *
 * The XZ plane is the ground, with Y being height.
 * 0 indexing.
 */

class Grid {
  private:
    int dimX, dimZ;
    std::vector< std::vector<int> > tiles;

    /** Pure */
    bool inBounds(int x, int z) const;

  public:
    // Constructor initializes all heights to 0.
    Grid(int x, int z);
    // TODO destructor?

    /** Pure */
    int getDimX() const;
    int getDimZ() const;
    // Returns y
    int get(int x, int z) const;

    /* Modify */
    void set(int x, int z, int targetY);

    /* Side-effect */
    // Represents ground height as '.'
    void dumpAscii() const;
};
