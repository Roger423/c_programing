
#include <stdio.h>

#define MAX 100

int main()
{
    int r, c;

    printf("Enter the number of rows and columns of the matrix:");
    scanf("%d %d", &r, &c);

    if (r != c) {
        printf("The matrix is not a identity matix because its number of rows not equal to its number of columns\n");
        return 0;
    }

    int m[MAX][MAX];
    printf("Enter the elements of matrix\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    printf("The elements of the matrix are:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i == j) {
                if (m[i][j] != 1) {
                    goto not_identity_matix;
                }
            } else {
                if (m[i][j] != 0) {
                    goto not_identity_matix;
                }
            }
        }
    }
    printf("\nMatrix is an identity matrix\n");
    return 0;

not_identity_matix:
    printf("\nMatrix is not an identity matrix\n");
    return 0;
}
