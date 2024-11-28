#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int src, dest; // File descriptors
    char buffer[BUFFER_SIZE];
    ssize_t n;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    if ((src = open(argv[1], O_RDONLY)) < 0 || 
        (dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror("Error");
        return 1;
    }

    while ((n = read(src, buffer, BUFFER_SIZE)) > 0)
        if (write(dest, buffer, n) != n) {
            perror("Write error");
            close(src);
            close(dest);
            return 1;
        }

    if (n < 0) perror("Read error");

    close(src);
    close(dest);
    printf("File copied successfully.\n");
    return 0;
}





"File copied succesfully"
