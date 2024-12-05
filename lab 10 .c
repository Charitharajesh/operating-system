#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX];
};

int main() {
    key_t key = ftok("msgqueue", 65); // Generate unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    struct msg_buffer message;

    // Process 1: Send a message
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from Process 1!");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }
    printf("Process 1: Message sent: %s\n", message.msg_text);

    // Process 2: Receive the message
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }
    printf("Process 2: Message received: %s\n", message.msg_text);

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        return 1;
    }

    return 0;
}
