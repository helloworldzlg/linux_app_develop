#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_func(int sign_no)
{
	if (sign_no == SIGINT) {
		printf("i have get SIGINT\n");
	} else if (sign_no == SIGQUIT) {

	}
}

int main()
{
	printf("waiting for signal SIGNAL or SIGQUIT...\n");

	signal(SIGINT, my_func);
	signal(SIGQUIT, my_func);

	pause();
	exit(0);
}