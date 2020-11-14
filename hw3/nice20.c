#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>
#include<sched.h>
#include<assert.h>
#include<errno.h>

void handle_err(int ret, char *func)
{
    perror(func);
    exit(EXIT_FAILURE);
}

int main(void)
{
    pid_t pid = -1;
    int ret = -1;
    struct sched_param sp;
    int max_rr_prio, min_rr_prio = -42;
    size_t cpu_set_size = 0;
    int new_priority;

    pid = getpid();
    printf("My pid is: %d\n", pid);

    sp.sched_priority = -1;
    ret = sched_getparam(pid, &sp);
    if (ret == -1)
        handle_err(ret, "sched_getparam");
    printf("My priority is %d\n", sp.sched_priority);

    ret = nice(-20);
    if (ret == -1)
        handle_err(ret, "nice");

    // Get new priority 
    errno = 0;
    new_priority = getpriority(PRIO_PROCESS, 0);
    printf("My new priority is %d\n", new_priority);

    return EXIT_SUCCESS;
}
