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

struct shmbuf {
	sem_t sem_1;
	sem_t sem_2;
	int buf[SIZE];
};

int main() {

	int fd = shm_open("table", O_RDONLY, 0666);
	
	struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ, MAP_SHARED, fd, 0);
	printf("Consumer mapped address: %p\n", shmp);
	
	sem_init(&shmp->sem_1, 1, 0);
	sem_init(&shmp->sem_2, 1, 0);
	
	sem_wait(&shmp->sem_1);
	printf("consumer started consuming data\n");
	for (int i = 0; i < SIZE; i++) {
		printf("Accessed shared memory buffer.\n");
		printf("Shared memory in buf[%d] is: ", i);
		printf("%d", (shmp->buf[i]));
	}
	
	sem_post(&shmp->sem_2);
	
	munmap(shmp, SIZE);
	close(fd);
	
	sem_unlink("sem_1");
	sem_unlink("sem_2");

	printf("Consumer exiting.\n");
	
	return 0;
}
