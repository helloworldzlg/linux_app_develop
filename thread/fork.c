#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t result;
	
	result = fork();
	if (result < 0)
	{
		printf("fork process fail!\n");
		exit;	
	}
	else if (0 == result)
	{
		printf("current process is child, pid is %d, ppid is %d\n", getpid(), getppid());		
	}
	else
	{
		printf("current process is parent, pid is %d\n", getpid());	
	}

	return 0;
}
