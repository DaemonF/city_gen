#pragma once
#include <list>
#include <assert.h>
#include <iostream>

using namespace std;

// TODO most of this stuff should be private to the generation part of the code

/**
 * Coordinate system notes:
 *
 * The XZ plane is the ground, with Y being height.
 * 0 indexing.
 * Height increases monotonically during generation, then a scale for each step is chosen last.
 */

// TODO use best-practice for immutable class
class Pt {
  private:
    int _x, _y, _z;

  public:
    Pt(int x, int y, int z) : _x(x), _y(y), _z(z) {
      assert(x >= 0);
      assert(y >= 0);
      assert(z >= 0);
    }
    int x() const { return _x; }
    int y() const { return _y; }
    int z() const { return _z; }

    Pt delta(int dx, int dy, int dz) const {
      return Pt(x() + dx, y() + dy, z() + dz);
    }
};

class Line {
  private:
    Pt _start, _end;

  public:
    // TODO label these methods too?
    Line(Pt start, Pt end) : _start(start), _end(end) {}
    Pt start() const { return _start; }
    Pt end() const { return _end; }

    bool goesLeft() const {
      return end().x() < start().x();
    }
    bool goesRight() const {
      return end().x() > start().x();
    }
    bool goesUp() const {
      return end().z() < start().z();
    }
    bool goesDown() const {
      return end().z() > start().z();
    }

    // Returns -1, 0, or 1
    int getDirectionX() const {
      if (goesRight()) {
        return 1;
      } else if (goesLeft()) {
        return -1;
      } else {
        return 0;
      }
    }
    int getDirectionZ() const {
      // TODO is this kinda backwards?
      if (goesUp()) {
        return -1;
      } else if (goesDown()) {
        return 1;
      } else {
        return 0;
      }
    }
};

// Represents a loop of line segments
// TODO place the loop at a fixed y, have 2D points inside
class Loop {
  private:
    list<Line> lines;
    friend ostream& operator<<(ostream &os, const Loop &loop);

    /** Modify */
    // Cuts the corner between the two lines starting at the iterator. Returns an iterator pointing
    // to the new version of the second line.
    list<Line>::iterator cutCorner(list<Line>::iterator it, int cutX, int cutZ);

    /** Side-effect */
    // Verifies the invariant that adjacent lines share a vertex.
    void assertValid();

  public:
    // TODO don't copy the list when we take it as a param?
    Loop(list<Line> initialLines);
    // TODO destructor?

    /** Pure */

    /* Modify */
    void cutAllCorners(int cutX, int cutZ);

    /* Side-effect */
    // Represents ground height (0) as ' ', each step up as an increasing letter.
    void dumpAscii() const;
};

// Begins at (0, y, 0)
list<Line> makeRectangle(int sizeX, int sizeZ, int y);
