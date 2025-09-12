/*
snprintf 是 "safe formatted string print" 的缩写，是在现代 C 语言编程中用于替代其不安全前辈 sprintf 的标准函数。
它的核心优势在于可以防止缓冲区溢出，是构建健壮、安全程序的必备工具。

它定义在头文件 <stdio.h> 中。

1. 函数原型 (Function Signature)

int snprintf(char *restrict str, size_t size, const char *restrict format, ...);

参数分解:

char *str:

目标缓冲区的指针。这是格式化后的字符串将被写入的地方。

size_t size:

最重要的参数。它指定了 str 指向的缓冲区的最大容量（以字节为单位）。snprintf 保证最多只会写入 size 个字节到缓冲区中，
这包括了字符串末尾的空终止符 \0。

const char *format:

格式化字符串。它与 printf 的格式化字符串完全一样，包含了普通字符和格式说明符（如 %d, %s, %f 等）。

... (可变参数):

一系列要根据 format 字符串中的格式说明符进行格式化的变量。

2. 核心行为与返回值 (Core Behavior & Return Value)
snprintf 的返回值是其最强大但也最容易被误解的部分。

返回值的定义是：

如果缓冲区足够大，本应写入的字符总数（不包括结尾的 \0）。

让我们分三种情况来理解：

情况一：缓冲区足够大 (成功写入)
当 size 大于或等于“本应写入的字符数 + 1”时，所有内容都能成功写入。

行为: 完整的格式化字符串被写入 str，并在末尾追加一个 \0。

返回值: 返回实际写入的字符数（不包括 \0）。这个返回值会小于 size。

示例:

char buffer[50];
int ret = snprintf(buffer, 50, "Hello, %s!", "world");

// 此时:
// buffer 的内容是 "Hello, world!"
// ret 的值是 13 (字符串 "Hello, world!" 的长度)
// 因为 13 < 50，所以写入成功。

情况二：缓冲区不足 (发生截断)
当 size 小于“本应写入的字符数 + 1”时，输出的字符串会被截断。

行为: snprintf 会写入尽可能多的字符（size - 1个），然后在缓冲区的末尾（str[size - 1]）强制放置一个 \0 来确保字符串是有效且安全的。

返回值: 同样返回本应写入的字符总数。这个返回值会大于或等于 size。这使得我们可以通过比较返回值和 size 来检测是否发生了截断。

示例:

char buffer[10];
int ret = snprintf(buffer, 10, "This is a very long string.");

// "This is a very long string." 的长度是 27
// 缓冲区大小为 10

// 此时:
// buffer 的内容是 "This is a" (9个字符 + 结尾的 '\0')
// ret 的值是 27
// 因为 27 >= 10，我们可以确定字符串被截断了。

这个特性非常有用，因为它告诉我们如果想完整地保存这个字符串，我们需要一个至少 27 + 1 = 28 字节的缓冲区。

情况三：发生错误
如果发生编码错误或其他错误，snprintf 会返回一个负值。这种情况比较少见。


*/

// 示例 1: 基本的字符串和数字格式化

#include <stdio.h>

int main() {
    char user_info[100];
    const char *name = "Alice";
    int age = 30;
    double score = 95.8;

    int ret = snprintf(user_info, sizeof(user_info), 
                       "User: %s, Age: %d, Score: %.1f", 
                       name, age, score);

    if (ret > 0 && ret < sizeof(user_info)) {
        printf("格式化成功!\n");
        printf("输出: %s\n", user_info);
        printf("写入了 %d 个字符。\n", ret);
    } else {
        printf("格式化失败或发生截断。\n");
        // 如果 ret >= sizeof(user_info)，说明发生了截断
    }

    return 0;
}
