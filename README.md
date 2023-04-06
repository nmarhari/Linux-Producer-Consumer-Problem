# Linux Producer Consumer Problem

This project includes a C implementation of the classic Producer-Consumer problem in Linux using semaphores, shared memory, threads, and two processes. This implementation is desgined to demonstrate how two processes with threads can communicate with each other using a shared memory buffer.

## Requirements

- Linux Operating System (Testing was done on Ubuntu in VirtualBox)
- GCC compiler
- Terminal

## Usage & Installation

1. Clone the repository OR download the files by navigating to the folder titled "C"
2. Open the folder in your Linux terminal
3. Make sure to have GCC up to date (gcc --version)
4. Compile using a couple commands:
  - gcc producer.c -pthread -lrt -o producer
  - gcc consumer.c -pthread -lrt -o consumer
  - ./producer & ./consumer &
5. Success!

## What this program is intended to do
In computer science, a producer-consumer example program is a program that simulates a scenario where there are two types of process, one producing data and the other consuming it. The producer process generates data items and puts them into a shared buffer, while the consumer process reads data from the buffer and processes it.

In this example program, the producer and consumer processes run concurrently, with the producer process generating data items at a certain rate and adding them to a shared buffer. The consumer process continuously reads data from the buffer and processes it, one item at a time. If the buffer is empty, the consumer process will wait until a new item is added by the producer process.

To prevent synchronization issues, the producer and consumer processes need to coordinate their actions. The producer process must ensure that the buffer is not full before adding a new data item to it, while the consumer process must ensure that the buffer is not empty before attempting to read from it. This coordination is achieved in this implementation through the use of a semaphore.

The producer-consumer example program is commonly used to illustrate how to implement process synchronization, potentially illustrate the similarities with multithreaded programming, and demonstrate the importance of using synchronization primitives to prevent race conditions and other synchronization issues.

In this particular implementation, the producer process will create a thread that will create a shared memory buffer and initialize two semaphores. The consumer process will create a thread that will attach to the shared memory buffer created by the producer process. The shared memory buffer contains the two semaphores as well as a table for the two processes/threads to exchange information. The processes/threads will exhibit mutual exclusion while passing arbitrary integers from the producer to the consumer. Once a specified number of iterations are complete, each thread will have finished their goal. The semaphores will be destroyed and the shared memory will be detached.

## Customization

You can customize the program by changing the following constants defined in **BOTH** the producer.c and consumer.c files:
(You must change the constants in both of the files or the program will not function properly.)
- `SIZE`: Size of the shared memory table
- `SHM_KEY`: Key used for the shared memory buffer
- `ITERATIONS`: Number of iterations you would like the two processes to attempt the critical section

## Example of usage
Note: `ITERATIONS` is set to 10
![1](https://user-images.githubusercontent.com/92116345/230514038-8c7e5eae-dbab-4788-bec3-b0291243365a.png)
![2](https://user-images.githubusercontent.com/92116345/230514047-ed2fb798-b3ed-44f8-9bdf-10ce706620ee.png)
![3](https://user-images.githubusercontent.com/92116345/230514055-a5f93304-62ed-40ca-ad54-e7545a013019.png)
![4](https://user-images.githubusercontent.com/92116345/230514058-1906a0d3-41ca-43bd-a7ec-03a6f1ac32c4.png)

## Contributors

- [nmarhari](https://github.com/nmarhari)
- This implementation was created by Nassim Marhari. It is based on the classic producer-consumer problem and uses the [System V IPC](https://man7.org/linux/man-pages/man3/shm_open.3.html) shared memory mechanism in Linux.
