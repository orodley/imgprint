#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "bmp.h"

int print_bmp(int fd)
{
	char buf[sizeof(BMP_header)];
	ssize_t bytes = read(fd, buf, sizeof(BMP_header));
	if (bytes == -1) {
		perror("error reading file");
		return 1;
	}

	BMP_header *header = (BMP_header*)buf;

	if (header->num_colors != 0 || header->bits_per_pixel < 8) {
		puts("Error: BMPs with color tables are currently unsupported");
		return 1;
	}

	if (header->bits_per_pixel % 8 != 0) {
		puts("Error: BMPs with bpp indivisible by 8 are currently unsupported");
		return 1;
	}

	size_t bytes_per_pixel = header->bits_per_pixel / 8;

	if (header->compression_method != BI_RGB) {
		puts("Error: compressed BMPs are currently unsupported");
		return 1;
	}

	char  *pixels = malloc(header->pixel_array_size);
	lseek(fd, header->pixels_offset, SEEK_SET);
	bytes = read(fd, pixels, header->pixel_array_size);
	if (bytes == -1) {
		perror("error reading file");
		free(pixels);
		return 1;
	}

	size_t column = 0;
	int    row    = header->height - 1;

	size_t row_width = bytes_per_pixel * header->width;
	if (row_width % 4 != 0)
		row_width += 4 - (row_width % 4);

	uint32_t max = 0;
	for (size_t n = 0; n < bytes_per_pixel / 3; n++) {
		max <<= 8;
		max |= 0xFF;
	}
	max *= 3;

	while (row > 0) {
		size_t i = row * row_width + (column * bytes_per_pixel);
		uint8_t b = pixels[i];
		uint8_t g = pixels[i + 1];
		uint8_t r = pixels[i + 2];

		if ((uint32_t)(r + g + b) < max / 2)
			putchar(' ');
		else
			putchar('#');

		column++;
		if (column == header->width) {
			putchar('\n');
			row--;
			column = 0;
		}
	}

	free(pixels);
	return 0;
}
