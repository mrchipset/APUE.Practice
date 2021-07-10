#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

int main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal error");
    }

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
            // printf("This is child process. Preparing for exec...\n");
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		} else if (pid > 0) /* parent */
        {
            printf("This parent process, create a child process:%ld\n", (long)pid);
        }

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}