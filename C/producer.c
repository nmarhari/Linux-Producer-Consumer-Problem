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
#define ITERATIONS 10

struct shmbuf {
	sem_t mutex;	// semaphore 1
	sem_t empty;	// semaphore 2
	int table[SIZE];
};

void* producer_thread(void* arg) {

	printf("Producer thread created.\n");
	
	time_t t;
	srand((unsigned) time(&t));
	int shm;
	
	struct shmbuf *shmptr;
	
	shm = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);
	if (shm == -1) printf("SHM key error\n");
	
	shmptr = shmat(shm, NULL, 0);
	if (shm == -1) printf("SHM attach error\n");
	
	sem_init(&shmptr->mutex, 1, 1);
	sem_init(&shmptr->empty, 1, SIZE);	
	
	for (int it = 0; it < ITERATIONS; it++) {
	
		sleep(1);
		sem_wait(&shmptr->mutex);
		printf("Producer entered...\n");
		
		int i, j = 1;
		sem_getvalue(&shmptr->empty, &i);
		while (i > 0) {
		
			int x = rand();
			shmptr->table[j] = x;
			sem_wait(&shmptr->empty);
			printf("Produced item %d\n", j);
			printf("Item %d produced = ", j);
			printf("%d\n", x);
			++j;
			sem_getvalue(&shmptr->empty, &i);

		}
		
		printf("Producer done producing items since the table is full.\n");
		
		sem_post(&shmptr->mutex);
	
	}
	
	printf("Producer thread has finished working.\n");
	
	sem_destroy(&shmptr->mutex);
	sem_destroy(&shmptr->empty);
	shmdt(shmptr);
}

int main() {
	
	pthread_t producer;
	pthread_create (&producer, NULL, producer_thread, NULL);
	
	pthread_join(producer, NULL);
	
	return 0;
}
