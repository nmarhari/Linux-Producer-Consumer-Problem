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

#define SIZE 2		// only 2 items in the buffer
#define SHM_KEY 0x1234

struct buffer {
	int id;		// for producer/consumer id
};

struct shmbuf {
	int sem_1;	// semaphore 1
	int sem_2;	// semaphore 2
	struct buffer buf[SIZE];
};

int main() {

	time_t t;
	srand((unsigned) time(&t));
	int x, y;
	
	struct shmbuf *shmptr;	// struct pointer
	
	x = shmget(SHM_KEY, sizeof(struct shmbuf), 0644|IPC_CREAT);	// create shm key for shared memory
	if (x == -1) printf("shm key error\n");
	
	shmptr = shmat(x, NULL, 0);					// attach shared memory
	if (shmptr == (void*)-1) printf("shm attach error\n");
	
	struct buffer consume_next;					// consume using for loop
	for (int i = 0; i < 10; i++) {
		while(shmptr->sem_1 == shmptr->sem_2) {			// while semaphore 1 and 2 are the same...
			printf("Consumer started consuming data.\n");	// consume
			sleep(1); 
			continue;
		}
		
	consume_next = shmptr->buf[shmptr->sem_2];			// next = buffer[semaphore 2]
	shmptr->sem_2 = (shmptr->sem_2 + 1) % SIZE;			// semaphore 2 = next % size
	sleep(1);
	printf("Consumer id: %d\n", consume_next.id);			// show consumer id
	}
	

	return 0;
}
