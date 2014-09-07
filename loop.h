#pragma once
#include <list>
#include <assert.h>

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
};

class Line {
  private:
    Pt _start, _end;

  public:
    Line(Pt start, Pt end) : _start(start), _end(end) {}
    Pt start() const { return _start; }
    Pt end() const { return _end; }
};

// Represents a loop of line segments
class Loop {
  private:
    std::list<Line> lines;

    /** Side-effect */
    // Verifies the invariant that adjacent lines share a vertex.
    void assertValid();

  public:
    // TODO don't copy the list when we take it as a param?
    Loop(std::list<Line> initialLines);
    // TODO destructor?

    /** Pure */

    /* Modify */

    /* Side-effect */
    // Represents ground height (0) as ' ', each step up as an increasing letter.
    void dumpAscii() const;
};
