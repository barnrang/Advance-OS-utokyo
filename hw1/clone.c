#include <sched.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STACK_SIZE (1024 * 1024)

int say_hello(){
    sleep(2);
    printf("My student id is 48206128\n");
    return 0;
}

int main()
{
    pid_t pid;
    int ret = -1;
    int wstatus = -42;
    char *stackTop;
    char *stack;

    stack = malloc(STACK_SIZE);
    stackTop = stack + STACK_SIZE;

    pid = clone(say_hello, stackTop, SIGCHLD);
    if (pid == -1)
    {
        perror("clone");
        return EXIT_FAILURE;
    }

    ret = waitpid(pid, &wstatus, 0);
    if (ret == -1)
    {
        perror("waitpid");
        return EXIT_FAILURE;
    }
    printf("Children status: %d\n", WEXITSTATUS(wstatus));

    return EXIT_SUCCESS;

}
