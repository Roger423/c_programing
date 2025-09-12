#include <stdlib.h>
#include <stdio.h>

/*
void alloc1(int *p) {
    p = malloc(sizeof(int));
    *p = 123;
}

int main() {
    int *ptr = NULL;
    alloc1(ptr);   // 传的是 NULL 的副本
    printf("%d\n", *ptr); // 崩溃：ptr 还是 NULL
}
*/


void alloc2(int **p) {
    *p = malloc(sizeof(int));
    **p = 123;
}

int main() {
    int *ptr = NULL;
    alloc2(&ptr);  // 传入 &ptr
    printf("%d\n", *ptr); // OK，输出 123
    free(ptr);
}

