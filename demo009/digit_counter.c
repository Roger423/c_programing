#include <stdio.h>

// 函数声明
int countDigits(int number);

int main() {
    int number;
    printf("请输入一个整数: ");
    scanf("%d", &number);
    
    int digitCount = countDigits(number);
    printf("数字 %d 有 %d 位数\n", number, digitCount);
    
    return 0;
}

// 计算数字位数的函数
int countDigits(int number) {
    if (number == 0) {
        return 1;
    }
    
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}
