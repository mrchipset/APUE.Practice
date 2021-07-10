#include "apue.h"
#include <fcntl.h>

static const int BUFFSIZE = 128;

/* demo for Figure 3.12 */
void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
        err_sys("fcntl F_GETFL error");
    } else
    {
        val |= flags;   /*  turn on flags */
        if (fcntl(fd, F_SETFL, val) < 0)
        {
            err_sys("fcntl F_SETFL error");
        }
    }
}

void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
        err_sys("fcntl F_GETFL error");
    } else
    {
        val &= ~flags;   /*  turn off flags */
        if (fcntl(fd, F_SETFL, val) < 0)
        {
            err_sys("fcntl F_SETFL error");
        }
    }
}

/* end demo for Figure 3.12 */

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    set_fl(STDOUT_FILENO, O_SYNC);
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
    {
        err_sys("read error");
    }

    exit(0);
}