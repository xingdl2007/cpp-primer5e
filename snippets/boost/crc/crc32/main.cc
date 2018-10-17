#include <boost/crc.hpp>
#include <iostream>

int main() {
  char buf[] = {'1', '2', '3', '4'};
  char buf2[] = {'5', '6', '7', '8', '9'};
  boost::crc_32_type crc32;
  crc32.process_bytes(buf, sizeof(buf));
  crc32.process_bytes(buf2, sizeof(buf2));
  std::cout << crc32.checksum() << std::endl;
}
