#include "polygon.h"
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

using namespace std;

void Polygon::dumpAscii() const {
  // Discover the bounds. Assumes the min is 0.
  int maxX = 0;
  int maxZ = 0;
  for (auto pt : points) {
    maxX = max(maxX, pt.x());
    maxZ = max(maxZ, pt.z());
  }

  // Fill out a lil grid
  vector< vector<int> > grid(maxX + 1, vector<int>(maxZ + 1));
  for (auto line : getLines()) {
    // This relies on the assumption that all lines are either horiz/vertical and have same height
    int x1 = line.start().x();
    int z1 = line.start().z();
    int x2 = line.end().x();
    int z2 = line.end().z();

    for (int x = min(x1, x2); x <= max(x1, x2); x++) {
      for (int z = min(z1, z2); z <= max(z1, z2); z++) {
        grid[x][z] = y;
      }
    }
  }

  // Print, interpreting each z as a row
  for (int z = 0; z <= maxZ; z++) {
    for (int x = 0; x <= maxX; x++) {
      int y = grid[x][z];
      char tile = y == 0 ? ' ' : 'a' + (y - 1);
      cout << tile;
    }
    cout << endl;
  }
}

// TODO ewwww
const Polygon *draw_polygon = NULL;

void draw() {
  if (draw_polygon != NULL) {
    draw_polygon->display_draw();
  }
}

void Polygon::display() const {
  int argc = 0;
  char *argv = NULL;
  glutInit(&argc, &argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Polygon display");

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glutDisplayFunc(draw);

  draw_polygon = this;
  // TODO never returns. doh.
  glutMainLoop();
  draw_polygon = NULL;
}

void Polygon::display_draw() const {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glScalef(.05f, .05f, 1);

  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_POLYGON);
  for (auto pt : points) {
    glVertex3f(pt.x(), pt.z(), 0);
  }
  glEnd();
  glFlush();
  glutSwapBuffers();
}
