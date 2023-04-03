// Nassim Marhari
// Linux Producer Consumer problem

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

const int SIZE = 2;
const int SPACE = (SIZE * sizeof(int));


int main() {

	sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
	sem_t *full = sem_open("full", O_CREAT,0666, 2);

	int shm = shm_open("table", O_RDONLY, 0666);
	
	int *tbl = (int*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm, 0);
	printf("Receiver mapped address: %p\n", tbl);
	
	sem_wait(mutex);
	printf("Consumer Mutex called wait...\n");
		
	for (int i = 0; i < SIZE; ++i) {
		printf("Consumer: %d\n", tbl[i]);
		sem_post(full);
		printf("Consumer Full called post.\n");
	}
	sem_post(mutex);
	printf("Consumer Mutex called post.\n");
		
	
	munmap(tbl, SPACE);
	
	sem_close(mutex);
	sem_close(full);


	return 0;
}
