#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

const char *policy_name(int policy) {
    switch (policy) {
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_FIFO: return "SCHED_FIFO";
        case SCHED_RR: return "SCHED_RR";
#ifdef SCHED_BATCH
        case SCHED_BATCH: return "SCHED_BATCH";
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE: return "SCHED_IDLE";
#endif
        default: return "UNKNOWN";
    }
}

int main(void) {
    pid_t pid = getpid();
    printf("Q5: priority comparison demo PID=%d\n", pid);
    fflush(stdout);

    unsigned long iter = 0;
    while (1) {
        int policy = sched_getscheduler(0);
        struct sched_param param;
        if (sched_getparam(0, &param) != 0) {
            perror("sched_getparam");
            return EXIT_FAILURE;
        }

        printf("Q5: PID=%d policy=%s priority=%d iter=%lu\n", pid, policy_name(policy), param.sched_priority, ++iter);
        fflush(stdout);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
