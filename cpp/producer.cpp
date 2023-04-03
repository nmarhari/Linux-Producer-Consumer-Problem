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
#include <cstdlib>
#include <stdio.h>
#include <string.h>

const int SIZE = 2048;

int main() {

	sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
	sem_t *full = sem_open("mutex", O_CREAT, 0666, 0);

	int table = shm_open("table", O_CREAT|O_RDWR, 0666);
	
	ftruncate(table, SIZE);
	
	char *tbl = (char*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, table, 0);
	
	const char *message0 = "hello";
	int i = 0;
	std::cout << "Sending message " << i << " to shared memory.\n";
	sprintf(tbl, "%s", message0);
	tbl += strlen(message0);
	
	sem_close(mutex);
	sem_close(full);


	return 0;
}
