#pragma once
#include <list>
#include <assert.h>
#include <iostream>
#include "primitives.h"

using namespace std;

// Represents a simple polygon
class Polygon {
  private:
    int y;
    list<Pt> points;
    friend ostream& operator<<(ostream &os, const Polygon &polygon);

  public:
    // TODO don't copy the list when we take it as a param?
    Polygon(list<Pt> initialPoints, int height);
    // TODO destructor?

    /** Pure */
    list<Line> getLines() const;

    /* Modify */
    void cutAllCorners(int cutX, int cutZ);

    /* Side-effect */
    // Represents ground height (0) as ' ', each step up as an increasing letter.
    void dumpAscii() const;

    // In OpenGL
    void display() const;
    void display_draw() const;
};

// Begins at (0, 0)
list<Pt> makeRectangle(int sizeX, int sizeZ);

// Returns a list of points that should replace pt2
list<Pt> cutCorner(Pt pt1, Pt pt2, Pt pt3, int cutX, int cutZ);
