#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

const char usage[] = "Usage: %s <filenname>\n";

#define READ_SIZE 2048

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf(usage, argv[0]);
		return 1;
	}

	//FILE *file = fopen(argv[1], "r");
	int fd = open(argv[1], O_RDONLY);
	char buf[READ_SIZE];
	ssize_t bytes;
	do {
		bytes = read(fd, buf, READ_SIZE);
		if (bytes == -1) {
			perror("error reading file");
			return 1;
		}

		write(STDOUT_FILENO, buf, bytes);
	} while (bytes == READ_SIZE);

	return 0;
}
