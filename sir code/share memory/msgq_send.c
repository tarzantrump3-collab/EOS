#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
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

    msgid = msgget(MSG_KEY, S_IRUSR | S_IWUSR | IPC_CREAT);
    if(msgid < 0) {
        perror("msgget");
        return -1;
    }

    printf("Sender connected to queue id: %d\n", msgid);

    /* Send TYPE 1 */
    message.mtype = 1;
    strcpy(message.mtext, "This is TYPE 1");

    printf("Sending TYPE 1\n");

    if(msgsnd(msgid, &message, sizeof(message.mtext), 0) < 0) {
        perror("msgsnd");
        return -1;
    }

    printf("TYPE 1 sent\n");
    sleep(10);

    /* Send TYPE 2 */
    message.mtype = 2;
    strcpy(message.mtext, "This is TYPE 2");
    printf("Sending TYPE 2\n");

    if(msgsnd(msgid, &message, sizeof(message.mtext), 0) < 0) {
        perror("msgsnd");
        return -1;
    }

    printf("TYPE 2 sent\n");

    /*if(msgctl(msgid, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        return -1;
    }*/

    return 0;
}
