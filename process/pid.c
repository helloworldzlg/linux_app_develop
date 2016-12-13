#include <stdio.h>

int main()
{
	printf("The PID of this process is %d\n", getpid());
	printf("The PPID of this process is %d\n", getppid());
	
	return 0;
}
