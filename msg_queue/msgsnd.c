#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE         (512)

struct message {
	long msg_type;
	char msg_text[BUFFER_SIZE];
};

int main()
{
	int qid;
	key_t key;
	struct message msg;

	key = ftok(".", 'a');
	if (-1 == key) {
		perror("ftok");
		exit(1);
	}

	qid = msgget(key, IPC_CREAT | 0666);
	if (-1 == qid) {
		perror("msgget");
		exit(1);
	}
	printf("open queue %d\n", qid);

	while(1) {
		printf("Enter some message to the queue:\n");
		if ((fgets(msg.msg_text, BUFFER_SIZE, stdin)) == NULL) {
			puts("no message");
			exit(1);
		}

		msg.msg_type = getpid();

		if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0) {
			perror("message postd");
			exit(1);
		}

		if (strncmp(msg.msg_text, "quit", 4) == 0) {
			break;
		}
	}

	exit(0);
}