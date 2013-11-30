#include <stdio.h>
#include "bmp.h"

void print_bmp(char buf[])
{
	puts("It's a BMP!");
	BMP_header *header = (BMP_header*)buf;
	printf(" size = %d\n", header->file_size);
	printf(" offset to pixel array = %d\n", header->pixels_offset);
}
