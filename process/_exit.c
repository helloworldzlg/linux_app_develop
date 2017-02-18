#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Using _exit\n");

	//printf("This is the content in buffer");

	printf("This is the content in buffer\n");

	/* add enter io buffer can output ok */

	_exit(0);
}