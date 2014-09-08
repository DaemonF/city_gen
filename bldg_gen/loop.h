#pragma once
#include <list>
#include <assert.h>
#include <iostream>
#include "primitives.h"

// TODO rename polygon

using namespace std;

// Represents a loop of points (aka a polygon :P )
// TODO place the loop at a fixed y, have 2D points inside
class Loop {
  private:
    list<Pt> points;
    friend ostream& operator<<(ostream &os, const Loop &loop);

  public:
    // TODO don't copy the list when we take it as a param?
    Loop(list<Pt> initialPoints);
    // TODO destructor?

    /** Pure */
    list<Line> getLines() const;

    /* Modify */
    void cutAllCorners(int cutX, int cutZ);

    /* Side-effect */
    // Represents ground height (0) as ' ', each step up as an increasing letter.
    void dumpAscii() const;
};

// Begins at (0, y, 0)
list<Pt> makeRectangle(int sizeX, int sizeZ, int y);

// Returns a list of points that should replace pt2
list<Pt> cutCorner(Pt pt1, Pt pt2, Pt pt3, int cutX, int cutZ);
