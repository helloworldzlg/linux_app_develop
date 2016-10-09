#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	if (0 == fork())
	{
		if (execlp("ps", "ps", "-ef", NULL) < 0)
		{
			perror("execlp error!");
		}
	}

	return 0;
}
