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
	if (mutex == SEM_FAILED) { perror("error creating mutex"); exit(EXIT_FAILURE); }
	sem_t *full = sem_open("full", O_CREAT, 0666, 2);
	if (full == SEM_FAILED) { perror("error creating full"); exit(EXIT_FAILURE); }
	sem_t *empty = sem_open("empty", O_CREAT, 0666, SIZE);
	if (empty == SEM_FAILED) { perror("error creating empty"); exit(EXIT_FAILURE); }
	printf("Opened semaphores.\n");

	int table = shm_open("table", O_CREAT|O_RDWR, 0666);
	if (table == -1) { perror("error creating memory"); exit(EXIT_FAILURE); }
	
	ftruncate(table, SIZE);
	
	int *tbl = (int*)mmap(0, SPACE, PROT_READ|PROT_WRITE, MAP_SHARED, table, 0);

	printf("Producer mapped address: %p\n", tbl);
	
	printf("producer started producing data\n");
	for (int i = 0; i < SIZE; i++) {
		sem_wait(empty);
		if (sem_wait(empty) == -1) { perror("error waiting on empty"); exit(EXIT_FAILURE); }
		printf("called wait(empty)");
		sem_wait(mutex);
		if (sem_wait(mutex) == -1) { perror("error waiting on mutex"); exit(EXIT_FAILURE); }		
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
