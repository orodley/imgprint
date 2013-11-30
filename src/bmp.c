#include <stdio.h>
#include "bmp.h"

void print_bmp(char buf[])
{
	puts("It's a BMP!");

	BMP_header *bmp_header = (BMP_header*)buf;
	printf(" file size = %d\n", bmp_header->file_size);
	printf(" offset to pixel array = %d\n", bmp_header->pixels_offset);

	DIB_header *dib_header = (DIB_header*)(bmp_header + 1);
	printf(" dimensions = %d x %d\n", dib_header->width, dib_header->height);
	printf(" bits per pixel = %d\n", dib_header->bits_per_pixel);
	printf(" number of colors = %d\n", dib_header->num_colors);
}
