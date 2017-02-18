#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pc, pr;

	pc = fork();
	if (pc < 0) {
		printf("fork error\n");
	} else if (0 == pc) {
		sleep(5);

		exit(0);
	} else {
		do {
			pr = waitpid(pc, NULL, WNOHANG);
			if (0 == pr) {
				printf("The child process has not exited\n");
				sleep(1);
			}	

		} while (0 == pr);	

		if (pr == pc) {
			printf("Get child exit code: %d\n", pr);
		} else {
			printf("some error occured\n");
		}
	}
}