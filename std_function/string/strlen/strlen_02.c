/*
strlen函数在统计字符串长度时不包含\0
strlen函数是C/C++语言中用于计算字符串长度的标准库函数，其核心功能是计算从字符串起始地址到第一个空字符（\0）之间的字符数。
因此，strlen函数的返回值并不包含\0本身。

工作原理
在C/C++中，字符串是以空字符\0作为结束标志的字符数组。strlen函数从给定的内存地址开始，逐个字节地检查字符，直到遇到\0为止。
它会返回在此过程中累计的字符数。

例如，对于一个定义为char str[] = "hello";的字符串，其在内存中的实际存储情况如下：

h	e	l	l	o	\0

当strlen(str)被调用时，它会计算'h', 'e', 'l', 'l', 'o'这五个字符，遇到\0时停止计数。因此，返回值为5。

strlen 与 sizeof 的区别
需要注意的是，strlen和sizeof在用于字符数组时有显著的区别：

strlen：是一个函数，它在运行时计算字符串的实际长度，即不包含\0的字符数。

sizeof：是一个运算符，它在编译时计算变量或类型所占用的内存空间大小（以字节为单位）。对于上面的str数组，sizeof(str)将返回6，
因为它包含了存储\0所需的1个字节。
*/

#include <stdio.h>
#include <string.h>

int main() {
    char my_string[] = "Hello World!";

    // 使用 strlen 获取字符串长度
    size_t length = strlen(my_string);

    // 使用 sizeof 获取数组占用的内存大小
    size_t size = sizeof(my_string);

    printf("字符串: %s\n", my_string);
    printf("strlen 的计算结果 (不包含 \\0): %zu\n", length);
    printf("sizeof 的计算结果 (包含 \\0): %zu\n", size);

    return 0;
}

/*
输出结果:

字符串: Hello World!
strlen 的计算结果 (不包含 \0): 12
sizeof 的计算结果 (包含 \0): 13

这个例子清晰地表明，strlen返回的是字符串的字符数量，而sizeof返回的是整个字符数组（包括\0）所占用的内存字节数。
*/
