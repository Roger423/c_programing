#include <stdio.h>

#define MAX 100

int ifexists(int arr[], int len, int val)
{
    if (len <= 0) return 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == val) return 1;
    }

    return 0;
}

int main()
{
    int m;
    int p[MAX], q[MAX];

    printf("Enter the length of the first array:");
    scanf("%d", &m);

    printf("Enter the %d elements of the first array\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    q[0] = p[0];

    int j = 1;
    for (int i = 1; i < m; i++) {
        if (!ifexists(q, j, p[i])) {
            q[j] = p[i];
            j++;
        }
    }

    printf("\nThe unique elements in the array are:\n");
    for (int i = 0; i < j; i++)
        printf("%d ", q[i]);
    printf("\n");

    return 0;
}