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

	int fd = shm_open("table", O_CREAT|O_RDWR, 0666);
	if (fd == -1) { perror("error creating memory"); exit(EXIT_FAILURE); }
	
	if(ftruncate(fd, sizeof(struct shmbuf)) == -1) { errExit("ftruncate");
	
	struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	printf("Producer mapped address: %p\n", fd);
							
	sem_init(&shmp->mutex, 1, 1);
	sem_init(&shmp->full, 1, 0);
	sem_init(&shmp->empty, 1, 2);
	
	printf("producer started producing data\n");
	for (int i = 0; i < SIZE; i++) {
		sem_wait(empty);
		printf("called wait(empty)");
		sem_wait(mutex);		
		printf("inside for loop prod");
		tbl[i] = i;
		printf("Producer: %d\n", i);
		sem_post(mutex);
		sem_post(full);
	}
	
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
