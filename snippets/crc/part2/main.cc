#include <stdint.h>
#include <string.h>
#include <iostream>

// the width of the CRC calculation and result.
// modify the typedef for a 16 or 32-bit CRC standard.
typedef uint32_t crc;

// 1 0000 0100 1100 0001 0001 1101 1011 0111
// #define POLYNOMIAL 0xd8  // 0b11011000

#define POLYNOMIAL 0x4C11DB7
#define WIDTH (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc crcSlow(uint8_t const message[], int nBytes) {
  crc remainder = 0;

  for (int byte = 0; byte < nBytes; ++byte) {
    remainder ^= message[byte] << (WIDTH - 8);

    for (uint8_t bit = 8; bit > 0; --bit) {
      // try to divide the current data bit.
      if (remainder & TOPBIT) {
        remainder = (remainder << 1) ^ POLYNOMIAL;
      } else {
        remainder = (remainder << 1);
      }
    }
  }

  // the final remainder is the CRC result;
  return remainder;
}

int main() {
  uint8_t buf[32];
  memset(buf, 0x0, sizeof(buf));

  std::cout << std::hex << crcSlow(buf, sizeof(buf)) << std::endl;
}
