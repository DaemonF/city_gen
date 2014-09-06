// TODO make these structs immutable?
struct Pt {
  int x, y, z;
};

struct Line {
  Pt start, end;
};

// Crawls clockwise; must start at the top-left corner of a valid loop-like structure that
// TODO is not described here.
//vector<Line> wallhug(int x, int z);
