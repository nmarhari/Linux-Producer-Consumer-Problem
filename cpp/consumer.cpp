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
const int BUF_SIZE = 2;

struct shmbuf {
	sem_t mutex;
	sem_t full;
	sem_t empty;
	int buf[BUF_SIZE];
};

int main() {

	int fd = shm_open("table", O_RDONLY, 0666);
	
	struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ, MAP_SHARED, fd, 0);
	printf("Consumer mapped address: %p\n", shmp);
	
	sem_init(&shmp->mutex, 1, 1);
	sem_init(&shmp->full, 1, 0);
	sem_init(&shmp->empty, 1, 2);
	
	printf("consumer started consuming data\n");
	for (int i = 0; i < SIZE; i++) {
		if(sem_wait(full) == -1) { perror("error waiting on full"); exit(EXIT_FAILURE); }
		if(sem_wait(mutex) == -1) { perror("error waiting on mutex"); exit(EXIT_FAILURE); }
		
		printf("inside for loop cons");
		printf("Consumer: %d\n", tbl[i]);
		sem_post(mutex);
		sem_post(empty);
	}
		
	
	munmap(tbl, SPACE);
	close(shm);

	
	sem_close(mutex);
	sem_close(full);
	sem_close(empty);
	
	sem_unlink("mutex");
	sem_unlink("full");
	sem_unlink("empty");

	printf("Consumer exiting.\n");
	
	return 0;
}
