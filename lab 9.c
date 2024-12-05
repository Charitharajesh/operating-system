#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    char *str = (char *)shmat(shmid, (void *)0, 0); // Attach to shared memory
    if (str == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Process 1: Write to shared memory
    printf("Process 1: Writing to shared memory\n");
    strcpy(str, "Hello from Process 1!");
    printf("Data written: %s\n", str);

    // Simulate Process 2: Read from shared memory
    printf("Process 2: Reading from shared memory\n");
    printf("Data read: %s\n", str);

    // Detach and destroy shared memory
    if (shmdt(str) == -1) {
        perror("shmdt failed");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        return 1;
    }

    return 0;
}
