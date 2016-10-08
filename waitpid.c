#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pc,pr;
	pc = fork();
	if (pc < 0)	
	{
		printf("Error fork.\n");	
	}
	else if (0 == pc)
	{
		sleep(5);
		exit(0);	
	}
	else
	{
		do {
			//pr = waitpid(pc, NULL, WNOHANG);
			pr = waitpid(pc, NULL, 0);
			if (0 == pr)
			{
				printf("the child process has not exited\n");
				sleep(1);
			}
		}while(0 == pr);

		if (pr == pc)
		{
			printf("get child %d\n", pr);
		}
		else
		{
			printf("some error occured.\n");
		}	
	}
	
	return 0;
}
