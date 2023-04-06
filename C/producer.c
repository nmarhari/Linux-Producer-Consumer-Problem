// Nassim Marhari
// Linux Producer Consumer problem
// producer.c

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

#define SIZE 2		// only 2 items in the table
#define SHM_KEY 0x1234

/*struct buffer {
	int id;		// for producer/consumer id
};*/

struct shmbuf {
	sem_t mutex;	// semaphore 1
	sem_t full;	// semaphore 2
	int table[SIZE];
};

void* producer_thread(void* arg) {

	printf("Producer thread created\n");
	
	time_t t;
	srand((unsigned) time(&t));
	int shm;
	
	struct shmbuf *shmptr;
	
	shm = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);
	if (shm == -1) printf("shm key error\n");
	
	shmptr = shmat(shm, NULL, 0);
	if (shm == (void*)-1) printf("shm attach error\n");
	
	sem_init(&shmptr->mutex, 1, 1);	
	
	sem_wait(&shmptr->mutex);
	printf("Producer entered...\n");
	
	for (int i = 1; i < 3; i++) {
	
		int x = rand();
		shmptr->table[i] = x;
		printf("Produced item %d\n", i);
		printf("Item %d produced = ", i);
		printf("%d\n", x);
	
	}
	
	printf("Producer done producing items since the table is full.\n");
	
	sem_post(&shmptr->mutex);
	
	sem_destroy(&shmptr->mutex);
	
}

int main() {
	
	pthread_t producer;
	pthread_create (&producer, NULL, producer_thread, NULL);
	
	pthread_join(producer, NULL);
	
	return 0;
}
