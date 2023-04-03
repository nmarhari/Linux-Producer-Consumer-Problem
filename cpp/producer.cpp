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
	sem_t mutex;
	sem_t full;
	sem_t empty;
	int buf[SIZE];
};

int main() {

	int fd = shm_open("table", O_CREAT|O_RDWR, 0666);
	if (fd == -1) { perror("error creating memory"); exit(EXIT_FAILURE); }
	
	if(ftruncate(fd, sizeof(struct shmbuf)) == -1) { errExit("ftruncate");
	
	struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (shmp == MAP_FAILED) { errExit("map failed");
	
	printf("Producer started producing data\n");
	for (int i = 0; i < SIZE; i++) {
		shmp->buf[i] = i;
		printf("Producer wrote to memory in buf[%d]\n", i);
	}
			
	sem_post(&shmp->sem_1);
				 
	sem_wait(&shmp->sem_2);
	
	munmap(tbl, SPACE);
	close(table);
	
	sem_close(mutex);
	sem_close(full);
	sem_close(empty);
	
	sem_unlink("mutex");
	sem_unlink("full");
	sem_unlink("empty");
	
	shm_unlink("table");
	printf("Producer exiting.\n");


	return 0;
}
