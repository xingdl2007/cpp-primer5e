#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  unsigned char const data[] = {0x31, 0x32, 0x33, 0x34, 0x35,
                                0x36, 0x37, 0x38, 0x39};
  
  std::size_t const data_len = sizeof(data) / sizeof(data[0]);

  boost::uint16_t const expected = 0x29B1;

  // simulate CRC-CCITT
  boost::crc_basic<16> crc_ccitt1(0x1021, 0xFFFF, 0, false, false);
  crc_ccitt1.process_bytes(data, data_len);

  assert(crc_ccitt1.checksum() == expected);

  // repeat iwth the optimal version(assuming a 16-bit type exists)
  boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false> crc_ccitt2;
  crc_ccitt2 = std::for_each(data, data + data_len, crc_ccitt2);
  assert(crc_ccitt2() == expected);

  std::cout << "All tests passed." << std::endl;
  return 0;
}
