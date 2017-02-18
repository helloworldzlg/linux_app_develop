#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t result;

	result = fork();
	if (result == -1) {
		printf("Fork error\n");
	} else if (result == 0) {
		printf("Children process, PID = %d, PPID = %d\n", getpid(), getppid());
		printf("The returned value is %d\n", result);				
	} else {
		printf("father process, PID = %d\n", getpid());
		printf("The returned value is %d\n", result);
	}
	
	return result;
}
