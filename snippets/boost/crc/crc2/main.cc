#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <ostream>

int main() {
  using boost::uint16_t;
  using boost::augmented_crc;

  // last 0 is a placeholder of CRC-16
  uint16_t data[6] = {2, 4, 31, 67, 98, 0};
  const uint16_t init_rem = 0x123;

  uint16_t crc1 = augmented_crc<16, 0x8005>(data, sizeof(data), init_rem);

  uint16_t const zero = 0;
  uint16_t const new_init_rem = augmented_crc<16, 0x8005>(&zero, sizeof(zero));

  boost::crc_basic<16> crc2(0x8005, new_init_rem);
  crc2.process_block(data, &data[5]);

  std::cout << crc1 << " " << crc2.checksum() << std::endl;
  assert(crc2.checksum() == crc1);

  std::cout << "All tests passed." << std::endl;
  return 0;
}
