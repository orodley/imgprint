#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "bmp.h"

#define SIGNATURE_LENGTH 2

const char usage[] = "Usage: %s <filenname>\n";

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf(usage, argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("error opening file");
		return 1;
	}

	char buf[SIGNATURE_LENGTH];
	ssize_t bytes = read(fd, buf, SIGNATURE_LENGTH);
	if (bytes == -1) {
		perror("error reading file");
		return 1;
	}

	lseek(fd, 0, SEEK_SET);

	switch (buf[0] << 8 | buf[1]) {
	case BMP_SIGNATURE:
		return print_bmp(fd);
	default:
		puts("Error: unrecognized file format");
		return 1;
	}
}
