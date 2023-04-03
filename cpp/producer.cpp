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
	sem_t *full = sem_open("mutex", O_CREAT, 0666, 2);

	int table = shm_open("table", O_CREAT|O_RDWR, 0666);
	
	ftruncate(table, SIZE);
	
	int *tbl = (int*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, table, 0);

	
	sem_wait(mutex);
	printf("sending this to there");
	printf("sender mapped address: %p\n", tbl);

	for (int i = 0; i < SIZE; i++) {
		tbl[i] = i;
		sem_wait(full);
	}
	sem_post(mutex);
	
	munmap(tbl, SPACE);
	
	close(table);
	
	sem_close(mutex);
	sem_close(full);


	return 0;
}
