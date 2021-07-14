#include <apue.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPEN_MAX 1024

int dup2_1(int fd1, int fd2)
{
    int open_fds[OPEN_MAX];
    int open_count = 0;
    int _fd;
    int i = 0;

    errno = 0;
    // check fd1 is opened.
    if ((open_fds[open_count++] = dup(fd1)) == -1)
        return -1;

    if (fd2 < 0 || fd2 > OPEN_MAX)
    {
        errno = EBADF;
        return -1;
    }

    // fd1 is equal to fd2. It's no need to create a new file description.
    if (fd1 == fd2)
        return fd2;

    if ((open_fds[open_count++] = dup(fd2)) >= 0)   // fd2 is already open.
    {
        // close the file first
        if (close(fd2) == -1)
        {
            return -1;
        }
    }

    do
    {
        _fd = dup(fd1);
        open_fds[open_count++] = _fd;
    } while (_fd != -1 && _fd != fd2);
    
    for (i = 0; i < open_count - 1; ++i)
    {
        close(open_fds[i]);
    }
    return _fd;
}

void test_mydup2(int (*fun_dup2)(int,int))
{
	// test case
	int old_fds[] = {0, 0, 2,  0, -1,  10,    -1, 65536};
	int new_fds[] = {0, 2, 2, 30,  2,  20, 65536, 65536};
	int count =  sizeof(old_fds)/sizeof(int);
	int ret;
	int i;
	// begin test
	for(i = 0; i < count; i++)
	{
		printf("dup2(%d, %d) : ", old_fds[i], new_fds[i]);
		ret = fun_dup2(old_fds[i], new_fds[i]);
		if(-1 == ret)
		{
			printf("%s\n", strerror(errno));
		}
		else if(ret == new_fds[i])
		{
			printf("success.\n");
			if(ret != 0 && ret != 1 && ret != 2)
				close(ret);
		}
		else 
		{
			printf("failed, not equal.\n");
		}
	}
	// test: dup stdout to 20, and print a string by 20
	printf("dup(1, 20), write(20, \"A test\\n\", 7) : ");
	fflush(stdout); // i don't know why fsync(1) not work here
	fun_dup2(1, 20);
	write(20, "A test\n", 7);
	printf("\n");
	close(20);
}

int main()
{
	// test my dup2
	printf("********* my dup2 ***********\n");
	test_mydup2(dup2_1);
	// test standard dup2 for a contrast
	printf("********standard dup2********\n");
	test_mydup2(dup2);
    // dup2_1(0, 30);
	return 0;
}
