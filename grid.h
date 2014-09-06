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
    bool inBounds(int x, int z);

  public:
    // Constructor initializes all heights to 0.
    Grid(int x, int z);

    /** Pure */
    int getDimX();
    int getDimZ();
    // Returns y
    int get(int x, int z);

    /* Modify */
    void set(int x, int z, int targetY);

    /* Side-effect */
    // Represents ground height as '.'
    void dumpAscii();
};

// TODO make these structs immutable?
/*struct Pt {
  int x, y, z;
};

struct Line {
  Pt start, end;
};
*/

//void fillRow(int z, int x1, int x2, int targetY);
//void fillColumn(int x, int z1, int z2, int targetY);

// Crawls clockwise; must start at the top-left corner of a valid loop-like structure that
// TODO is not described here.
//vector<Line> wallhug(int x, int z);

// something to find rectangle inside line segments... although wall-hugging is just for generating
// quads. don't retain these structures later. bldg will have the quads.
