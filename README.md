# Linux Producer Consumer Problem

This project includes a C implementation of the classic Producer-Consumer problem in Linux using semaphores, shared memory, and two processes. This implementation is desgined to demonstrate how two processes can communicate with each other using a shared memory buffer.

## Requirements

- Linux Operating System (Testing done on Ubuntu in VirtualBox)
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

The producer program will create two items to put into a shared memory buffer, and a producer will consume those items from the buffer until it is empty. This implementation is intended to demonstrate mutual exclusion and uses semaphores in order to accomplish that goal. The producer and consumer processes shall notify the user of what is happening internally. A screenshot of example commands to run the processes and their output will be attached below.

## Example of usage
https://imgur.com/UNW5Y3b

## Customization

You can customize the program by changing the following constants defined in the producer.c or consumer.c file:
C VERSION:
- `SIZE`: Size of the shared buffer

## Contributors

- [nmarhari](https://github.com/nmarhari)
- This implementation was created by [nmarhari]. It is based on the classic producer-consumer problem and uses the System V IPC shared memory mechanism in Linux. (https://man7.org/linux/man-pages/man2/shmget.2.html)

## License

This implementation is released under the MIT License. You are free to use, modify, and distribute this code, as long as you include the original license file and attribution to the original author.
