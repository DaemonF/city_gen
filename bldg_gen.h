// TODO this might not even be valid C yet ;)

// TODO make these immutable?
struct FlatLineSegment {
  int x1, y1, x2, y2;
  int height;
}

class Grid {
  // 0 indexing
  // TODO name things appropriately

  // Pure
  int getDimX();
  int getDimY();
  // return value is height
  int get(int x, int y);
  list<FlatLineSegment> wallhug(int x, int y);  // must start at top-left corner, it'll crawl clockwise

  // Modify
  void set(int x, int y, int height);
  void fillRow(int y, int x1, int x2, int height);
  void fillColumn(int x, int y1, int y2, int height);

  // Side-effect
  void dumpAscii();
};

// something to find rectangle inside line segments... although wall-hugging is just for generating
// quads. don't retain these structures later. bldg will have the quads.
