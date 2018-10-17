// Force use of assert, interesting
#if defined(NDEBUG)
#undef NDEBUG
#endif

#include <boost/functional/hash.hpp>
#include <cassert>

class Point {
  int x_, y_;

public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}

  bool operator==(Point const &other) const {
    return x_ == other.x_ && y_ == other.y_;
  }

  friend std::size_t hash_value(Point const &p);
};

std::size_t hash_value(Point const &p) {
  std::size_t seed = 0;
  boost::hash_combine(seed, p.x_);
  boost::hash_combine(seed, p.y_);
  return seed;
}

int main() {
  boost::hash<Point> point_hasher;
  Point p1(0, 0);
  Point p2(1, 2);
  Point p3(4, 1);
  Point p4 = p1;

  assert(point_hasher(p1) == point_hasher(p4));

  assert(point_hasher(p1) != point_hasher(p2));
  assert(point_hasher(p1) != point_hasher(p3));
  return 0;
}
