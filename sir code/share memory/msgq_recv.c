#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#define MSG_KEY 1234

typedef struct msgbuf {
    long mtype;
    char mtext[100];
} msgbuf_t;

int main()
{
    int msgid;
    msgbuf_t message;

    msgid = msgget(MSG_KEY, S_IRUSR | S_IWUSR);
    if(msgid < 0) {
        perror("msgget");
        return -1;
    }

    printf("Receiver connected to queue id: %d\n", msgid);

    printf("Waiting ONLY for TYPE 2 message...\n");

    /*
     * BLOCKS until message type 1 arrives
     */
    if(msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) < 0) {
        perror("msgrcv");
        return -1;
    }

    printf("Received message type: %ld\n", message.mtype);
    printf("Received message: %s\n", message.mtext);
    return 0;
}
