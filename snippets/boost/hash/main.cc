
#include <boost/functional/hash.hpp>
#include <iostream>
#include <set>
#include <stdint.h>
#include <unordered_map>
#include <utility>

typedef std::pair<uint32_t, uint32_t> Track;

// hash_combine and hash_value, which is not necessary if you use boost
struct TrackHash {
  std::size_t operator()(const Track &t) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, boost::hash_value(t.first));
    boost::hash_combine(seed, boost::hash_value(t.second));
    return seed;
  }
};

int main() {
  std::set<Track> pset;

  pset.insert({1, 2});
  pset.insert({1, 4});

  // boost::hash works with std::pair
  std::unordered_map<Track, uint64_t, boost::hash<Track>> illegal;
  for (auto &k : pset)
    ++illegal[k];

  for (const auto &p : illegal)
    std::cout << p.second << std::endl;


  // set as hash key
}
