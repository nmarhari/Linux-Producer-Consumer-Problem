// Nassim Marhari
// Linux Producer Consumer problem

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define SIZE 2
#define SHM_KEY 0x1234

struct buffer {
	int id;
};

struct shmbuf {
	int sem_1;
	int sem_2;
	struct buffer buf[SIZE];
};

int main() {

	time_t t;
	srand((unsigned) time(&t));
	int x, y;
	
	struct shmbuf *shmptr;
	
	x = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);
	if (x == -1) printf("shm key error\n");
	
	shmptr = shmat(x, NULL, 0);
	if (shmptr == (void*)-1) printf("shm attach error\n");
	
	struct buffer consume_next;
	for (int i = 0; i < SIZE; i++) {
		while(shmptr->sem_1 == shmptr->sem_2) {
			printf("Consumer started consuming data.\n");
			sleep(1); 
			continue;
		}
		
	consume_next = shmptr->buf[shmptr->sem_2];	
	shmptr->sem_2 = (shmptr->sem_2 + 1) % SIZE;
	sleep(1);
	printf("Consumer id: %d\n", consume_next.id);
	}
	

	return 0;
}