#include <stdio.h>

int main(void)
{
    int array[5];
    int i;
    int *p;

    for (i = 0; i < 5; i++)
    {
        array[i] = i;
    }

    for (p = &array[0], i = 0; p != &array[5]; p++, i++)
    {
        printf("array[%d] --> %d\n", i, *p);
    }

    return 0;
}