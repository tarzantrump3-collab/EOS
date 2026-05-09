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
    printf("Q9: ps/chrt correlation demo PID=%d\n", pid);
    fflush(stdout);

    while (1) {
        int policy = sched_getscheduler(0);
        struct sched_param param;
        if (sched_getparam(0, &param) != 0) {
            perror("sched_getparam");
            return EXIT_FAILURE;
        }
        printf("Q9: PID=%d policy=%s rtprio=%d\n", pid, policy_name(policy), param.sched_priority);
        fflush(stdout);
        sleep(3);
    }

    return EXIT_SUCCESS;
}
