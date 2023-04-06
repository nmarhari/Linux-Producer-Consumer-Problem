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

#define SIZE 2		// only 2 items in the buffer
#define SHM_KEY 0x1234

/*struct buffer {
	int id;		// for producer/consumer id
};*/

struct shmbuf {
	sem_t mutex;	// semaphore 1
	sem_t sem_2;	// semaphore 2
	int buffer[SIZE];
};

void* consumer_thread(void* arg) {
	
	printf("consumer thread created\n");
	
	time_t t;
	srand((unsigned) time(&t));
	int shm;
	
	struct shmbuf *shmptr;
	
	shm = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);
	if (shm == -1) printf("shm key error\n");
	
	shmptr = shmat(shm, NULL, 0);
	if (shm == (void*)-1) printf("shm attach error\n");
	
	sleep(1);
	
	sem_wait(&shmptr->mutex);
	printf("Consumer entered...\n");
	
	for (int i = 0; i < 2; i++) {
		printf("consumed item %d\n", i);
		
	}

	printf("Consumer done consuming items.\n");

	sem_post(&shmptr->mutex);

	return 0;
}

int main() {


	pthread_t consumer;
	pthread_create (&consumer, NULL, consumer_thread, NULL);
	
	pthread_join(consumer, NULL);

	printf("test");

	return 0;
}
