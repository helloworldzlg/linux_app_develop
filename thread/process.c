#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("the PID of this process is %d\n", getpid());
	printf("the PPID of this process is %d\n", getppid());

	return 0;
}
