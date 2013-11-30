#include <stddef.h>
#include <stdio.h>
#include "bmp.h"

int print_bmp(char buf[])
{
	BMP_header *bmp_header = (BMP_header*)buf;
	DIB_header *dib_header = (DIB_header*)(bmp_header + 1);

	if (dib_header->num_colors != 0 || dib_header->bits_per_pixel < 8) {
		puts("Error: BMPs with color tables are currently unsupported");
		return 1;
	}

	if (dib_header->bits_per_pixel != 24) { // Just support one size for now
		puts("Error: BMPs with bpp other than 24 are currently unsupported");
		return 1;
	}

	char *pixels = buf + bmp_header->pixels_offset;
	size_t column = 0;
	for (size_t i = 0; i < dib_header->pixel_array_size; i += 3) {
		uint8_t b = pixels[i];
		uint8_t g = pixels[i + 1];
		uint8_t r = pixels[i + 2];

		if (r + g + b < (256 * 3) / 2)
			putchar(' ');
		else
			putchar('#');

		column++;
		if (column == dib_header->width) {
			putchar('\n');

			if (column % 4 != 0)
				i += 4 - (column % 4);

			column = 0;
		}
	}

	return 0;
}
