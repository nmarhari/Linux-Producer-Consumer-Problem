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

const int SIZE = 2048;
const int SPACE = (SIZE * sizeof(int));
const int ITEMS = 2;

int main() {


	sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
	sem_t *full = sem_open("full", O_CREAT, 0666, 2);
	printf("Opened semaphores.\n");

	int table = shm_open("table", O_CREAT|O_RDWR, 0666);
	
	ftruncate(table, SIZE);
	
	int *tbl = (int*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, table, 0);

	printf("Producer mapped address: %p\n", tbl);
	
	printf("1");
	sem_wait(mutex);
	printf("Producer called wait on MUTEX...");
	
	for (int i = 0; i < ITEMS; i++) {
		tbl[i] = i;
		printf("Producer: %d\n", i);
		sem_wait(full);
		printf("Producer Full called wait...\n");
	}
	sem_post(mutex);
	printf("Producer Mutex called post.\n");
	
	munmap(tbl, SPACE);
	shm_unlink("table");
	
	close(table);
	
	sem_close(mutex);
	sem_close(full);
	
	sem_unlink("mutex");
	sem_unlink("full");
	
	sem_destroy(mutex);
	sem_destroy(full);
	printf("Both semaphores destroyed.\n");


	return 0;
}
