#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd;
    
    if ((fd = open("hello.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600) < 0)){
        perror("open fail\n");
        exit(1);
    } else {
        printf("open file: hello.txt %d\n", fd);
    }

    if (close(fd) < 0) {
        perror("close\n");
        exit(1);
    } else 
        printf("close hello.txt\n");
    
    exit(0);
}
