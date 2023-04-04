# Linux Producer Consumer Problem

This is a C++ implementation of the classic Producer-Consumer problem in Linux semaphores, System V IPC shared memory, and two processes.

## Requirements

- Linux Operating System (Testing done on Ubuntu)
- GCC compiler

## Usage & Installation

1. Clone the repository OR download the files
2. Navigate to the folder
3. Compile using a couple commands:
  - g++ producer.cpp -pthread -lrt -o producer
  - g++ consumer.cpp -pthread -lrt -o consumer
  - ./producer & ./consumer &
4. Success!

## What this program is intended to do
The producer program will create 2 items to put into a shared memory buffer, and a producer will consume those items from the buffer until it is empty. This implementation is intended to demonstrate mutual exclusion, and uses semaphores in order to accomplish that goal. The producer and consumer processes shall notify the user what is happening internally.

## Customization

You can customize the program by changing the following constants defined in the producer.cpp or consumer.cpp file:
- `SIZE`: Size of the shared buffer
- `SEM_1`: Change to a different semaphore
- `SEM_2`: Change to a different semaphore
- `SEM_1, 1, 0`: Change last number in initialize to modify semaphore properties
- `SEM_2, 1, 0`: Change last number in initialize to modify semaphore properties

## Contributors

- [nmarhari](https://github.com/nmarhari)
- This implementation was created by [nmarhari]. It is based on the classic producer-consumer problem and uses the System V IPC shared memory mechanism in Linux. (https://man7.org/linux/man-pages/man2/shmget.2.html)

## License

This implementation is released under the MIT License. You are free to use, modify, and distribute this code, as long as you include the original license file and attribution to the original author.
