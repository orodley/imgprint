#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "bmp.h"

const char usage[] = "Usage: %s <filenname>\n";

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf(usage, argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	char buf[READ_SIZE];
	ssize_t bytes = read(fd, buf, READ_SIZE);
	if (bytes == -1) {
		perror("error reading file");
		return 1;
	}

	switch (buf[0]) {
	case BMP_SIGNATURE:
		print_bmp(buf);
		return 0;
	default:
		puts("Error: unrecognized file format");
		return 1;
	}
}
