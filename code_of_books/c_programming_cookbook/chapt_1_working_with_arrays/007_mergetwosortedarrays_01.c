// 下面的代码有什么问题
#include <stdio.h>

#define MAX 100

int main() 
{
    int m, n;
    int i, j, k;
    int p[MAX], q[MAX], r[MAX];

    printf("Enter the length of the first array:");
    scanf(" %d", &m);
    printf("Enter %d elements of the first array in sorted order\n", m);
    for (i = 0; i < m; i++)
        scanf(" %d", &p[i]);
    
    printf("Enter the length of the second array:");
    scanf(" %d", &n);
    printf("Enter %d elements of the second array in sorted order\n", n);
    for (j = 0; j < n; j++)
        scanf(" %d", &q[j]);
    
    i = j = k = 0;
    while(i < m && j < n) {
        if (p[i] < q[j]) {
            r[k] = p[i];
            i++;
            k++;
        } else if (p[i] > q[j]) {
            r[k] = q[j];
            j++;
            k++;
        } else {
            r[k] = p[i];
            i++;
            k++;
            r[k] = q[j];
            j++;
            k++;
        }
    }

    while(i < m) {
        r[k] = p[i];
        i++;
        k++;
    }
    while (j < n) {
        r[k] = q[j];
        j++;
        k++;
    }

    printf("\nThe combined sorted array is:\n");
    for(i = 0; i < k; i++)
        printf("%d ",r[i]);
    printf("\n");

    return 0;
}
