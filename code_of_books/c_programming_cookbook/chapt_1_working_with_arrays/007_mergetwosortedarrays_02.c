#include <stdio.h>
#include <stdlib.h> // 为了使用 malloc and free

// 将合并逻辑封装成一个函数，这是更好的编程实践
void merge(int p[], int m, int q[], int n, int r[]) {
    int i = 0, j = 0, k = 0;

    // --- 优化的主循环 ---
    // 只要两个数组都还有元素，就进行比较
    while (i < m && j < n) {
        // 使用两路分支，更简洁高效
        if (p[i] <= q[j]) {
            r[k++] = p[i++]; // 复制p的元素，然后移动p和r的指针
        } else {
            r[k++] = q[j++]; // 复制q的元素，然后移动q和r的指针
        }
    }

    // --- 处理剩余元素 ---
    // 此时，下面两个while循环最多只会执行一个
    // 如果数组p还有剩余元素，全部复制到r
    while (i < m) {
        r[k++] = p[i++];
    }

    // 如果数组q还有剩余元素，全部复制到r
    while (j < n) {
        r[k++] = q[j++];
    }
}

int main() {
    int p[] = {1, 3, 5, 7, 9};
    int q[] = {2, 4, 6, 8, 10};
    int m = sizeof(p) / sizeof(p[0]);
    int n = sizeof(q) / sizeof(q[0]);

    // 动态分配内存，避免栈上的大小限制
    int* r = (int*)malloc((m + n) * sizeof(int));
    if (r == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    merge(p, m, q, n, r);

    printf("The combined sorted array is:\n");
    for (int i = 0; i < m + n; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");

    free(r); // 释放动态分配的内存
    return 0;
}
