#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	if (fork() == 0) {
		if (execlp("ps", "ps", "-ef", NULL) < 0) {
			printf("execlp error\n");
		}
	}
	
	return 0;
}

