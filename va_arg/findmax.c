#include <stdio.h>
#include <stdarg.h>

int findMax(int count, ...) {
    va_list args;
    va_start(args, count);

    int max = va_arg(args, int); // 获取第一个参数
    for (int i = 1; i < count; i++) {
        int num = va_arg(args, int); // 获取后续参数
        if (num > max) {
            max = num; // 更新最大值
        }
    }

    va_end(args);
    return max;
}

int main() {
    printf("最大值是: %d\n", findMax(5, 1, 9, 3, 7, 4)); // 传递任意数量的整数
    printf("最大值是: %d\n", findMax(3, 5, 15, 10));
    printf("最大值是: %d\n", findMax(4, 12, 22, 5, 14));
    return 0;
}
