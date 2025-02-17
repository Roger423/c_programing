#include <stdio.h>

void hello(void)
{
    fprintf(stderr, "hello!\n");
}

void func(void)
{
    void *buff[10];
    static int i;

    for (i = 0; i < 100; i++) {
        buff[i] = hello;
    }
}

int main(void)
{
    int buff[1000];
    buff[999] = 10;

    func();

    return 0;
}
