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
	printf("dimensions: %d x %d\n\n", header->width, header->height);

	if (header->num_colors != 0 || header->bits_per_pixel < 8) {
		puts("Error: BMPs with color tables are currently unsupported");
		return 1;
	}

	if (header->bits_per_pixel != 24) { // Just support one size for now
		puts("Error: BMPs with bpp other than 24 are currently unsupported");
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

	size_t row_width = 3 * header->width;
	if (row_width % 4 != 0)
		row_width += 4 - (row_width % 4);

	while (row > 0) {
		size_t i = row * row_width + (column * 3);
		uint8_t b = pixels[i];
		uint8_t g = pixels[i + 1];
		uint8_t r = pixels[i + 2];

		if (r + g + b < (256 * 3) / 2)
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
