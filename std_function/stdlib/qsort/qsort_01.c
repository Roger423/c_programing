/*
1. 函数原型

在 stdlib.h 头文件中定义：

void qsort(
    void *base,        // 待排序数组的起始地址
    size_t nmemb,      // 数组元素个数
    size_t size,       // 每个元素的大小（字节数）
    int (*compar)(const void *, const void *)  // 比较函数指针
);

2. 参数解释

base
指向待排序数组的首地址，可以是任意类型的数组（如 int[], double[], struct[]）。
由于 qsort 是通用排序函数，它用 void * 来表示数组。

nmemb
数组中的 元素个数。

size
每个元素所占字节数，通常通过 sizeof(type) 获取。

compar
函数指针，定义了 两个元素的比较规则。
原型：

int compar(const void *a, const void *b);


返回值 < 0 ：表示 a < b

返回值 = 0 ：表示 a == b

返回值 > 0 ：表示 a > b


注意事项

比较函数必须满足严格弱序关系
否则结果可能不确定。例如不要写不对称的比较规则。

整数比较要小心溢出
直接 return (*(int*)a - *(int*)b); 在极大数值时可能溢出。更安全写法：

int cmp_int(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}


qsort 并不稳定
相等元素的相对顺序可能会改变。如果需要稳定排序，需要自己实现（如 mergesort）。

时间复杂度
平均情况 O(n log n)，最坏情况也通常会做优化避免退化。
*/

//(1) 排序整数数组

#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);  // 升序
    // return (*(int *)b - *(int *)a);  // 降序
}

int main() {
    int arr[] = {42, 7, 19, 73, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), cmp_int);

    printf("排序结果: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
