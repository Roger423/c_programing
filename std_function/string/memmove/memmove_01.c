/*
memmove 是 C 语言标准库 <string.h> 中定义的一个函数，用于从一个缓冲区移动指定字节数的数据到另一个缓冲区。
它最显著的特点是能够正确处理源缓冲区和目标缓冲区内存区域重叠的情况。

函数原型
void *memmove(void *dest, const void *src, size_t n);

参数说明
void *dest: 指向目标内存区域的指针，拷贝的数据将存放在这里。

const void *src: 指向源内存区域的指针，要拷贝的数据从这里开始。

size_t n: 要拷贝的字节数。

返回值
该函数返回一个指向目标内存区域 dest 的指针。

###核心功能与 memcpy 的关键区别

memmove 的功能与 memcpy 非常相似，都是用于内存拷贝。然而，它们之间存在一个至关重要的区别：

memcpy：当源内存区域和目标内存区域发生重叠时，memcpy 的行为是未定义的。这意味着结果可能是不可预测的，可能会导致数据损坏。

memmove：memmove 被设计为可以安全地处理内存重叠的情况。它通过一种特殊的方式进行拷贝，确保即使 src 和 dest 的区域有交集，
源数据在被覆盖之前也能够被正确地复制。可以将其理解为，memmove 会先将源数据拷贝到一个临时的中间缓冲区，然后再从这个临时缓冲区拷贝到目标地址。

因此，基本原则是：

当你不确定源和目标内存区域是否会重叠时，或者明确知道它们会重叠时，请使用 memmove。

当你确定内存区域不会重叠时，可以使用 memcpy，因为它的实现可能稍快一些（尽管现代编译器通常会对此进行优化）。
*/

/*
使用场景与示例
1. 非重叠内存区域拷贝
在这种情况下，memmove 的作用和 memcpy 完全相同。
*/

#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    printf("源字符串: %s\n", src);

    // 将 src 中的内容拷贝到 dest
    memmove(dest, src, strlen(src) + 1); // +1 是为了拷贝字符串末尾的空字符 '\0'

    printf("目标字符串: %s\n", dest);

    return 0;
}

// 输出:

// 源字符串: Hello, World!
// 目标字符串: Hello, World!
