#include <stdio.h>

#define MAX 100

int main()
{
    int r, c;

    printf("Enter the number of rows and columns of the matirx:");
    scanf("%d %d", &r, &c);

    if (r != c) {
        printf("The matix is not a identity matix because its number of rows not equal to its number of columns\n");
        return 0;
    }

    int m[MAX][MAX];
    printf("Enter the elements of matrix\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    printf("The elements of the matix are:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    int is_identity_matix = 1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i == j) {
                if (m[i][j] != 1) {
                    is_identity_matix = 0;
                    break;
                }
            } else {
                if (m[i][j] != 0) {
                    is_identity_matix = 0;
                    break;
                }
            }
        }
    }

    if (is_identity_matix) {
        printf("\nMatrix is an identity matrix\n");
    } else {
        printf("\nMatrix is not an identity matrix\n");
    }

    return 0;
}