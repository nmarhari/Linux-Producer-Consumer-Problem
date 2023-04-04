Linux Producer Consumer Problem

This is a C++ implementation of the classic Producer-Consumer problem in Linux semaphores, System V IPC shared memory, and two processes.

## Requirements

- Linux Operating System (Testing done on Ubuntu)
- GCC compiler

## Usage & Installation

1. Clone the repository OR download the files
2. Navigate to the folder
3. Compile using [in progress]
4. Success!

## Customization

You can customize the program by changing the following constants defined in the producer.cpp or consumer.cpp file:
- `SIZE`: Size of the shared buffer
- `MUTEX`: Change to a different semaphore
- `FULL`: Change to a different semaphore
- `EMPTY`: Change to a different semaphore

## Contributors

- [nmarhari](https://github.com/nmarhari)
- This implementation was created by [nmarhari]. It is based on the classic producer-consumer problem and uses the System V IPC shared memory mechanism in Linux. (https://man7.org/linux/man-pages/man2/shmget.2.html)

## License

This implementation is released under the MIT License. You are free to use, modify, and distribute this code, as long as you include the original license file and attribution to the original author.
