#include <stdio.h>

#define MAX 100

int main()
{
    int array[MAX];
    int n;
    printf("Please input the number of elements of the array:");
    scanf(" %d", &n);

    for (int i = 0; i < n; i++) {
        printf("Please input the value of the array at position %d:", i);
        scanf(" %d", &array[i]);
    }

    printf("Initiate array values:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int pos, insert_val;
    printf("Please input the insert position: ");
    scanf(" %d", &pos);
    printf("Please input the insert value:");
    scanf(" %d", &insert_val);

    for (int i = n; i > pos; i--) {
        array[i + 1] = array[i];
    }

    array[pos] = insert_val;

    printf("Array values after insertion:\n");
    for (int i = 0; i < n + 1; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}