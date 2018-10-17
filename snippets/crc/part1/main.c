#include <stdint.h>

#define POLYNOMIAL 0xd8  // 0b11011000

uint8_t crcNaive(uint8_t const message) {
  uint8_t remainder;

  // initially, the dividend is the remainder.
  remainder = message;

  // for each bit position in the message
  for (uint8_t bit = 8; bit > 0; --bit) {
    // if the uppermost bit is a 1...
    if (remainder & 0x80) {
      remainder ^= POLYNOMIAL;
    }

    // shift the next bit of the message into the remainder
    remainder = (remainder << 1);
  }

  // return only the relevant bits of the remainder as CRC.
  return (remainder >> 4);
}
