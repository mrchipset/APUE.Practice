#include <apue.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPEN_MAX 1024

int main()
{
	int fd = open("test.txt", O_RDWR | O_APPEND | O_SYNC);
	if (fd == -1)
	{
		err_exit(-1, "open failed\n");
	}

	write(fd, "World\n", 6);
	
	int r;
	if ((r = lseek(fd, 0, SEEK_SET)) == -1)
	{
		close(fd);
		err_exit(-1, "lseek failed\n");
	}

	write(fd, "Hello", 5);

	if ((r = lseek(fd, 0, SEEK_SET)) == -1)
	{
		close(fd);
		err_exit(-1, "lseek failed\n");
	}

	char str[32];
	read(fd, str, 15);
	printf("%s\n", str);
	close(fd);

	return 0;
}
