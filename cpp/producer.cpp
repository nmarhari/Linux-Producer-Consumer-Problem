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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct shmbuf {
	sem_t sem_1;
	sem_t sem_2;
	int buf[SIZE];
};

int main() {

	int fd = shm_open("table", O_CREAT|O_RDWR, 0666);
	if (fd == -1) { perror("error creating memory"); exit(EXIT_FAILURE); }
	
	if(ftruncate(fd, sizeof(struct shmbuf)) == -1) { errExit("ftruncate"); }
	
	struct shmbuf *shmp = (shmbuf*)mmap(NULL, sizeof(*shmp), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (shmp == MAP_FAILED) { errExit("map failed"); }
	printf("Producer mapped address: %p\n", shmp);
	
	sem_init(&shmp->sem_1, 1, 0);
	sem_init(&shmp->sem_2, 1, 0);
	
	printf("Producer started producing data\n");
	for (int i = 0; i < SIZE; i++) {
		shmp->buf[i] = i;
		printf("Producer wrote to memory in buf[%d]\n", i);
	}
			
	sem_post(&shmp->sem_1);
	printf("sempost sem_1 producer\n");
				 
	sem_wait(&shmp->sem_2);
	printf("semwait sem_2 producer\n");
	
	munmap(shmp, SIZE);
	close(fd);
	
	sem_unlink("sem_1");
	sem_unlink("sem_2");
	
	shm_unlink("table");
	printf("Producer exiting.\n");


	return 0;
}
