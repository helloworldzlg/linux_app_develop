#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int ret;

	pid = fork();
	if (pid < 0) {
		printf("fork error\n");
		exit(1);
	}

	if (0 == pid) {
		printf("child(pid: %d) is waiting for any signal\n", getpid());
		raise(SIGSTOP);
		exit(0);
	} else {
		if (0 == waitpid(pid, NULL, WNOHANG)) {
			if (0 == (ret = kill(pid, SIGKILL))) {
				printf("parent kill %d\n", pid);
			}
		}

		waitpid(pid, NULL, 0);
		exit(0);
	}
}