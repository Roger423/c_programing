/*
1. strstr —— 查找子字符串

头文件：

#include <string.h>


函数原型：

char *strstr(const char *haystack, const char *needle);


功能：

在字符串 haystack 中查找第一次出现的子字符串 needle。

返回 指向第一次匹配位置的指针，如果没找到，返回 NULL。
*/

//用法示例：

#include <stdio.h>
#include <string.h>

int main() {
    const char *str = "Hello, world!";
    const char *sub = "world";

    char *pos = strstr(str, sub);
    if (pos) {
        printf("Found substring at position: %ld\n", pos - str);
        printf("Remaining string: %s\n", pos);
    } else {
        printf("Substring not found\n");
    }
    return 0;
}

/*
输出：

Found substring at position: 7
Remaining string: world!
*/
