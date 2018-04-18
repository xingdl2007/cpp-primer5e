//
// Created by xing on 4/3/18.
//

#include <stdio.h>

void byteorder() {
  union {
    short value;
    char bytes[sizeof(short)];
  } test;

  test.value = 0x0102;
  if (test.bytes[0] == 0x1 && test.bytes[1] == 0x2) {
    printf("big endian\n");
  } else if (test.bytes[0] == 0x2 && test.bytes[1] == 0x1) {
    printf("little endian\n");
  } else {
    printf("unknown");
  }
}

int main() {
  byteorder();
}