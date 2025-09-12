/*
头文件：

#include <string.h>


函数原型：

char *strchr(const char *str, int c);


功能：

在字符串 str 中查找字符 c 第一次出现的位置。

返回 指向该字符的指针，如果没找到，返回 NULL。

注意：如果 c == '\0'，则返回指向字符串末尾 '\0' 的指针。
*/

//用法示例：

#include <stdio.h>
#include <string.h>

int main() {
    const char *str = "Hello, world!";
    char ch = 'o';

    char *pos = strchr(str, ch);
    if (pos) {
        printf("Found character '%c' at position: %ld\n", ch, pos - str);
        printf("Remaining string: %s\n", pos);
    } else {
        printf("Character not found\n");
    }
    return 0;
}

/*
输出：

Found character 'o' at position: 4
Remaining string: o, world!
*/