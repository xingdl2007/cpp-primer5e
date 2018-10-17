#include <boost/functional/hash.hpp>
#include <iostream>
#include <set>
#include <stdint.h>
#include <unordered_map>
#include <utility>

typedef std::set<std::pair<uint32_t, uint32_t>> Track;

int main() {
  // set as hash key
  std::unordered_map<Track, uint64_t, boost::hash<Track>> illegal;

  Track t1 = {{1, 2}, {3, 4}};
  Track t2 = t1;
  Track t3 = {{3, 4}, {1, 2}};
  Track t4 = {{1, 2}, {3, 4}, {5, 6}};

  ++illegal[t1];
  ++illegal[t2];
  ++illegal[t3];
  ++illegal[t4];

  auto copy = illegal;

  for (auto &p : copy)
    std::cout << p.second << std::endl;
}
