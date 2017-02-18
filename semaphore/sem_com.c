#include "sem_com.h"

int init_sem(int sem_id, int init_value)
{
	union semum sem_union;
	sem_union.val = init_value;

	if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
		perror("Initialize semaphore");
		return -1;
	}

	return 0;
}

int del_sem(int sem_id)
{
	union semum sem_union;
	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1) {
		perror("delete semaphore");
		return -1;
	}
}

int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_b, 1) == -1) {
		perror("p operation");
		return -1;
	}

	return 0;
}