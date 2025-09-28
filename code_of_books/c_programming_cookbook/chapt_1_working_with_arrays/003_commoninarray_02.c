/*
对003_commoninarray_01.c中的代码进行优化：

性能分析
代码的核心逻辑是这三个嵌套的循环：

for (int i = 0; i < m; i++): 遍历第一个数组 p。

for (int j = 0; j < n; j++): 遍历第二个数组 q。

ifexists(r, k, p[i]): 在找到一个共同元素后，遍历结果数组 r 以确保不重复添加。

假设第一个数组的长度是 m，第二个数组的长度是 n，结果数组中不重复的共同元素个数是 k。

外层两个循环的计算量是 O(m×n)。

在最坏的情况下，每次找到一个共同元素，都需要调用 ifexists 函数。ifexists 函数本身是一个线性搜索，其时间复杂度是 O(k)。

因此，整个算法的时间复杂度近似为 O(m×n×k)。当 m 和 n 很大时，这个效率是非常低的。

例如，如果 m=100, n=100，并且它们有很多共同元素，k 也接近100，那么总的操作次数可能在 100×100×100=1,000,000 这个量级，性能较差。

可优化点
主要优化的方向是降低时间复杂度，避免三重循环。以下是几种常见的优化方法，从简单到高效。

方法一：排序 + 双指针法
这是最经典、最高效的优化方法之一，尤其是在不允许使用额外数据结构（如哈希表）时。

思路：

首先对两个数组 p 和 q 进行升序排序。

然后使用两个指针，比如 i 指向 p 的开头，j 指向 q 的开头。

比较 p[i] 和 q[j] 的值：

如果 p[i] < q[j]，说明 p[i] 不可能是共同元素，将 i 向后移动一位。

如果 p[i] > q[j]，说明 q[j] 不可能是共同元素，将 j 向后移动一位。

如果 p[i] == q[j]，说明找到了一个共同元素。将它存入结果数组 r，然后同时将 i 和 j 向后移动一位。

在存入结果数组 r 时，需要注意避免重复。一个简单的处理方法是：在存入一个元素后，检查结果数组 r 的最后一个元素是否和当前要存入的元素相同。

复杂度分析：

排序 p 数组的时间复杂度是 O(mlogm)。

排序 q 数组的时间复杂度是 O(nlogn)。

双指针遍历一遍的时间复杂度是 O(m+n)。

总时间复杂度为 O(mlogm+nlogn)，这远优于原来的 O(m×n×k)。


*/

#include <stdio.h>
#include <stdlib.h> // for qsort

#define MAX 100

// qsort 需要的比较函数
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int p[MAX], q[MAX], r[MAX];
    int m, n;

    // ... (用户输入部分和原代码相同) ...
    printf("Enter the length of the first array:");
    scanf(" %d", &m);
    printf("Enter %d elements of the first array:\n", m);
    for (int i = 0; i < m; i++)
        scanf(" %d", &p[i]);
    
    printf("Enter the length of the second array:");
    scanf(" %d", &n);
    printf("Enter %d elements of the second array:\n", n);
    for (int i = 0; i < n; i++)
        scanf(" %d", &q[i]);

    // 1. 对两个数组进行排序
    qsort(p, m, sizeof(int), compare);
    qsort(q, n, sizeof(int), compare);

    int k = 0;
    int i = 0, j = 0;

    // 2. 使用双指针查找交集
    while (i < m && j < n) {
        if (p[i] < q[j]) {
            i++;
        } else if (p[i] > q[j]) {
            j++;
        } else { // p[i] == q[j]
            // 检查是否与r中最后一个元素重复
            if (k == 0 || r[k - 1] != p[i]) {
                r[k] = p[i];
                k++;
            }
            i++;
            j++;
        }
    }
    
    // ... (输出部分和原代码相同) ...
    if (k > 0) {
        printf("\nThe common elements in the two arrays are:\n");
        for (int i = 0; i < k; i++)
            printf("%d ", r[i]);
        printf("\n");
    } else {
        printf("There are no common elements in the two arrays\n");
    }

    return 0;
}


/*
方法二：使用哈希表（空间换时间）
如果允许使用额外的存储空间，哈希表是查找问题的利器。

思路：

创建一个哈希集合（Hash Set）。

遍历其中一个较短的数组（假设是 p），将其所有元素存入哈希集合中。

遍历另一个数组 q，对于 q 中的每一个元素，检查它是否存在于哈希集合中。

如果存在，说明是共同元素，就把它存入结果数组 r 中。为了保证结果 r 中的元素不重复，可以再用一个哈希集合来存放结果。

复杂度分析：

将 p 数组元素存入哈希表的时间复杂度是 O(m)。

遍历 q 数组并查询哈希表的时间复杂度是 O(n) （平均情况下哈希表查询是 O(1)）。

总时间复杂度为 O(m+n)。这是理论上能达到的最优时间复杂度。

空间复杂度为 O(m+k)，需要额外的空间来存储哈希表和结果集。

C 语言标准库没有内置哈希表，需要自己实现或使用第三方库。对于简单的整数，可以用一个大布尔数组来模拟哈希表（如果整数范围不大且非负）。
*/