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
	
	struct buffer produce_next;
	for (int i = 0; i < 10; i++) {
		while((shmptr->sem_1 + 1) % SIZE == shmptr->sem_2) {
			printf("Producer started producing data.\n");
			sleep(1); 
			continue;
		}
	produce_next.id = shmptr->sem_1;
	shmptr->buf[shmptr->sem_1] = produce_next;
	shmptr->sem_1 = (shmptr->sem_1 + 1) % SIZE;
	
	printf("Producer id: %d\n", produce_next.id);
	
	}
	
	return 0;
}
