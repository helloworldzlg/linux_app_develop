#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE       (2048)

int main()
{
	pid_t pid;
	int shmid;
	char* shm_addr;
	char flag[] = "WROTE";
	char* buff;

	shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666);
	if (shmid < 0) {
		perror("shmget");
		exit(1);
	} else {
		printf("create shared-memory: %d\n", shmid);
	}

	system("ipcs -m");

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	} else if (pid == 0) {
		shm_addr = shmat(shmid, 0, 0);
		if (shm_addr == (void*)-1) {
			perror("child: shmat");
			exit(1);
		} else {
			printf("child attach shared-memory: %p\n", shm_addr);
		}
		system("ipcs -m");

		while (strncmp(shm_addr, flag, strlen(flag))) {
			printf("child: wait for enable data...\n");
			sleep(5);
		}

		strcpy(buff, shm_addr + strlen(flag));
		printf("child: shared-memory: %s\n", buff);

		if (shmdt(shm_addr) < 0) {
			perror("shmdt");
			exit(1);
		} else {
			printf("child: deattach shared-memory\n");
		}

		system("ipcs -m");

		if (shmctl(shmid, IPC_RMID, NULL) == -1) {
			perror("child: shmctl(IPC_RMID)\n");
			exit(1);
		} else {
			printf("delete shared-memory\n");
		}

		system("ipcs -m");
	} else {
		shm_addr = shmat(shmid, 0, 0);
		if (shm_addr == (void*)-1) {
			perror("parent: shmat");
			exit(1);
		} else {
			printf("parent: attach shared-memory: %p\n", shm_addr);
		}

		sleep(1);
		printf("\nInput some string:\n");
		fgets(buff, BUFFER_SIZE, stdin);
		strncpy(shm_addr + strlen(flag), buff, strlen(buff));
		strncpy(shm_addr, flag, strlen(flag));

		if ((shmdt(shm_addr)) < 0) {
			perror("parent: shmdt");
			exit(1);
		} else {
			printf("parent: deattach shared-memory\n");
		}

		system("ipcs -m");

		waitpid(pid, NULL, 0);
		printf("finished\n");
	}

	exit(0);
}
