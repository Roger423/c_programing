//compile cmd: gcc -std=c11 -pthread -o datarace datarace.c

#include <stdio.h>
#include <threads.h>

_Atomic long long counter = 0;

int thrd_proc1(void * arg)
{
    struct timespec interv = {0, 20};
    
    for (size_t x = 0; x < 50000; x++)
    {
        counter += 1;
        thrd_sleep(&interv, 0);
    } 
    return 0;
}

int thrd_proc2(void * arg)
{
    struct timespec interv = {0, 30};
    
    for (size_t x = 0; x < 50000; x++)
    {
        counter -= 1;
        thrd_sleep(&interv, 0);
    }
    return 0;
}

int main(void)
{
    thrd_t t0, t1;

    thrd_create(&t0, thrd_proc1, 0);
    thrd_create(&t1, thrd_proc2, 0);

    thrd_join(t0, &(int){0});
    thrd_join(t1, &(int){0});

    printf("Value of counter: %lld\n", counter);

    return 0;
}
