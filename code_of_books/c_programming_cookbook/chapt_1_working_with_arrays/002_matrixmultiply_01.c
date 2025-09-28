#include <stdio.h>

int main()
{
    int mat_a[2][3], mat_b[3][4], mat_r[2][4];
    int i, j, k;

    printf("Enter elements of the first matrix of order 2 x 3 \n");

    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            scanf(" %d", &mat_a[i][j]);

    printf("Enter elements of the second matrix of order 3 x 4 \n");

    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            scanf(" %d", &mat_b[i][j]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            mat_r[i][j] = 0;
            for (k = 0; k < 3; k++) {
                mat_r[i][j] = mat_r[i][j] + mat_a[i][k] * mat_b[k][j];
            }
        }
    }
    printf("-------------------------------------\n");
    printf("Matrix A:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) 
            printf("%d ", mat_a[i][j]);
        printf("\n");
    }

    printf("\n");

    printf("Matrix B:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) 
            printf("%d ", mat_b[i][j]);
        printf("\n");
    }

    printf("\n");

    printf("Multiplied matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) 
            printf("%d ", mat_r[i][j]);
        printf("\n");
    }

    printf("-------------------------------------\n");

    return 0;
}
