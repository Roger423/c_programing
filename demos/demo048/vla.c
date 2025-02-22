#include <stdio.h>

int main(void)
{
    int size1, size2, size3;

    printf("Please input three intigers: ");
    scanf("%d%d%d", &size1, &size2, &size3);

    int array1[size1];
    int array2[size2][size3];

    for (int i = 0; i < size1; i++)
    {
        array1[i] = i;
    }
    for (int i = 0; i < size2; i++)
        for (int j = 0; j < size3; j++)
        {
            array2[i][j] = i * size3 + j;
        }
    printf("-------------------------------------------------\n");
    printf("Value of array1:\n");
    for (int i = 0; i < size1; i++)
    {
        printf("array1[%d] --> %d\n", i, array1[i]);
    }

    printf("-------------------------------------------------\n");
    printf("Value of array2:\n");
    for (int i = 0; i < size2; i++)
    {
        for (int j = 0; j< size3; j++)
        {
            printf("%d\t", array2[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------\n");
    printf("size of array1 --> %zd\n", sizeof(array1));
    printf("size of array2 --> %zd\n", sizeof(array2));
    printf("-------------------------------------------------\n");

    return 0;
}
