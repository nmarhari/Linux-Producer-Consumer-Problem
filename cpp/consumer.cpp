// Nassim Marhari
// Linux Producer Consumer problem

#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <cstdlib.h>
#include <stdio.h>
#include <string.h>

const int SIZE = 2048;

int main() {

	sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
	sem_t *full = sem_open("mutex", O_CREAT,0666, 0);

	int shm = shm_open("table", O_RDWR, 0666);
	
	int *tbl = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm, 0);
	
	int x = rand();
	
	std::cout << "Receiving message " << i << " from shared memory.\n";
	
	printf("%s", (char*)tbl);
	
	sem_close(mutex);
	sem_close(full);


	return 0;
}
