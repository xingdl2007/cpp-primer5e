#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define barrier() __asm__ __volatile__ ("":::"memory");

uint32_t DecodeFixed32(const char*ptr, bool little) {
	if(little) {
		uint32_t result;
		memcpy(&result, ptr, sizeof(result));
		return result;
	}else {
		return ptr[0] | (ptr[1] << 8) | (ptr[2] <<16) | (ptr[3] << 24);
	}
}

int main() {
	barrier();
	const char data[] = {1,2,3,4};
	printf("%#x\n", DecodeFixed32(data, true));
	printf("%#x\n", DecodeFixed32(data, false));
	return 0;
}
