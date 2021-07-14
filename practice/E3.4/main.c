#include <apue.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPEN_MAX 1024

int main()
{
	int fd = open("test.txt", O_RDWR);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	// if (fd > 2)
	// 	close(fd);
	printf("\nI'm from stdio\n");
	return 0;
}
