#include <stdio.h>

int main(void)
{
    int array[5];
    int i;
    printf("---------------------------------\n");
    for (i = 0; i < 5; i++)
    {
        array[i] = i;
    }
    printf("---------------------------------\n");
    for (i = 0; i < 5; i++)
    {
        printf("array[%d] --> %d\n", i, array[i]);
    }
    printf("---------------------------------\n");
    for (i = 0; i < 5; i++)
    {
        printf("&array[%d] --> %p\n", i, &array[i]);
    }
    printf("---------------------------------\n");
    return 0;
}