#include <stdint.h>

#define BMP_SIGNATURE 0x424D

typedef struct BMP_header
{
	uint16_t signature;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint16_t pixels_offset;
} __attribute__((packed)) BMP_header;

void print_bmp(char buf[]);
