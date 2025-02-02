//compile cmd: gcc -std=c11 -pthread -o mthrs mthrs.c

#include <stdio.h>
#include <threads.h>

int thread_proc(void * arg)
{
    unsigned cnt = 5;
    struct timespec interv = {1, 0};

    while (cnt--)
    {
        printf("Thread --> %s\n", (char *)arg);
        thrd_sleep(&interv, 0);
    }

    return 0;
}

int main(void)
{
    thrd_t t0, t1;

    thrd_create(& t0, thread_proc, "A");
    thrd_create(& t1, thread_proc, "b");

    thrd_detach(t0);
    thrd_detach(t1);

    printf("Thread --> Main\n");
    thrd_sleep(& (struct timespec) {1, 500000000}, 0);
    printf("Thread --> Main\n");
    // printf("+\t");
    // printf("\n");

    thrd_exit(0);
    // return 0;
}

