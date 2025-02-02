/*
vfprintf 是一个标准 C 库函数，用于将格式化输出写入到指定的文件流中。与 fprintf 类似，
但 vfprintf 接受一个 va_list 类型的可变参数列表，而不是一组不定数量的参数。这使得它适合在实现其他可变参数函数时使用。

用法:
int vfprintf(FILE *stream, const char *format, va_list ap);

参数：
FILE *stream：指定输出目标的文件流指针，例如 stdout、stderr 或者使用 fopen 打开的文件指针。
const char *format：格式字符串，包含普通字符和格式说明符。
va_list ap：可变参数列表，通常通过 va_start 和 va_arg 宏来处理。

返回值：
返回写入的字符数（不包括终止的空字符），如果发生错误则返回一个负值。

*/

#include <stdio.h>
#include <stdarg.h>

void printError(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf(stderr, format, args);

    va_end(args);
}

int main() {
    printError("Error: %s at line %d\n", "File not found", 42);
    return 0;
}

/*
声明函数 printError：
void printError(const char *format, ...)
printError 函数接收一个格式字符串和任意数量的后续参数。

初始化可变参数列表：
va_list args;
va_start(args, format);

调用 vfprintf：
vfprintf(stderr, format, args);

结束可变参数处理：
va_end(args);
使用 va_end 结束可变参数的处理。

总结
vfprintf 是一个非常有用的函数，尤其在实现自定义的格式化输出函数时。它允许您将格式化输出写入到指定的文件流中，
并提供处理可变参数的灵活性。

*/
