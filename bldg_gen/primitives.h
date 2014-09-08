#pragma once
#include <assert.h>

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
    Line(Pt start, Pt end) : _start(start), _end(end) {
      int cnt = 0;
      cnt += goesLeft() ? 1 : 0;
      cnt += goesRight() ? 1 : 0;
      cnt += goesUp() ? 1 : 0;
      cnt += goesDown() ? 1 : 0;
      assert(cnt == 1);
    }

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
      if (goesUp()) {
        return -1;
      } else if (goesDown()) {
        return 1;
      } else {
        return 0;
      }
    }
};
