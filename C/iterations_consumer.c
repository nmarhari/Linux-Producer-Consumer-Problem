// Nassim Marhari
// Linux Producer Consumer problem
// consumer.c

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

void* consumer_thread(void* arg) {
	
	printf("Consumer thread created.\n");
	
	time_t t;
	srand((unsigned) time(&t));
	int shm;
	
	struct shmbuf *shmptr;
	
	shm = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);
	if (shm == -1) printf("SHM key error\n");
	
	shmptr = shmat(shm, NULL, 0);
	if (shm == -1) printf("SHM attach error\n");
	
	sleep(1);
	
	for (int it = 0; it < ITERATIONS; it++) {
	
		sleep(1);
		sem_wait(&shmptr->mutex);
		printf("Consumer entered...\n");
		
		int i, j = 1;
		sem_getvalue(&shmptr->empty, &i);
		while (i < SIZE) {
			
			int x;
			x = shmptr->table[j];
			sem_post(&shmptr->empty);
			printf("Consumed item %d\n", j);
			printf("Item %d consumed = ", j);
			printf("%d\n", x);
			++j;
			sem_getvalue(&shmptr->empty, &i);
			
		}

		printf("Consumer done consuming items since the table is empty.\n");

		sem_post(&shmptr->mutex);
	}
}

int main() {


	pthread_t consumer;
	pthread_create (&consumer, NULL, consumer_thread, NULL);
	
	pthread_join(consumer, NULL);

	return 0;
}
