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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

const int SIZE = 2;

struct shmbuf {
	sem_t sem_1;
	sem_t sem_2;
	int buf[SIZE];
};

int main() {

	int fd = shm_open("table", O_RDONLY, 0666);
	if (fd == -1) { perror("error creating memory"); exit(EXIT_FAILURE); }
	
	struct shmbuf *shmp = (shmbuf*)mmap(NULL, sizeof(*shmp), PROT_READ, MAP_SHARED, fd, 0);
	if (shmp == MAP_FAILED) { errExit("map failed"); }
	printf("Consumer mapped address: %p\n", shmp);
	
	for (int i = 0; i < SIZE; i++) {
		printf("semwait sem_1 consumer\n");
		if (sem_wait(&shmp->sem_1) == -1) errExit("sem_wait");
		printf("consumer started consuming data\n");
		printf("Accessed shared memory buffer.\n");
		printf("Shared memory in buf[%d] is: ", i);
		printf("%d", (shmp->buf[i]));
	}
	
	sem_post(&shmp->sem_2);
	printf("sempost sem_2 consumer\n");
	
	munmap(shmp, SIZE);
	close(fd);
	
	sem_unlink("sem_1");
	sem_unlink("sem_2");

	printf("Consumer exiting.\n");
	
	return 0;
}
