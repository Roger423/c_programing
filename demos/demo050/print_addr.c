#include <stdio.h>
#include <stdlib.h>

int global_var;
static int file_static_var;

void func1(void)
{
    int func1_var;
    static int local_static_var;

    printf("&func1_var --> %p\n", (void*)&func1_var);
    printf("&local_static_var --> %p\n\n", (void*)&local_static_var);
}

void func2(void)
{
    int func2_var;

    printf("&func2_var --> %p\n\n", (void*)&func2_var);
}

int main(void)
{
    int *p;

    printf("func1 --> %p\n", (void*)func1);
    printf("func2 --> %p\n\n", (void*)func2);

    printf("string literal --> %p\n\n", (void*)"abc");

    printf("&global_var --> %p\n\n", (void*)&global_var);

    printf("&file_static_var --> %p\n\n", (void*)&file_static_var);

    func1();
    func2();

    p = malloc(sizeof(int));
    printf("malloc address --> %p\n\n", (void*)p);

    return 0;
}

