//alignment of struct

#include <stdio.h>

struct Hoge
{
    char char1;
    int int1;
    char char2;
    double double1;
    char char3;
};

int main(void)
{
    struct Hoge hoge;

    printf("hoge size --> %d\n", (int)sizeof(hoge));

    printf("hoge addr    --> %p\n", (void*)&hoge);
    printf("char1 addr   --> %p\n", (void*)&hoge.char1);
    printf("int1 addr    --> %p\n", (void*)&hoge.int1);
    printf("char2 addr   --> %p\n", (void*)&hoge.char2);
    printf("double1 addr --> %p\n", (void*)&hoge.double1);
    printf("char3 addr   --> %p\n", (void*)&hoge.char3);

    return 0;
}
