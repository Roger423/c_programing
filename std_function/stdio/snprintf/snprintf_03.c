
// 示例 3: 检测截断并重新分配内存
// 这是一个高级用法，展示了 snprintf 返回值的强大之处。
// 注：vsnprintf 是 snprintf 的可变参数列表版本，常用于封装自己的打印函数。

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// 一个动态格式化字符串的函数
char* dynamic_format_string(const char* format, ...) {
    va_list args1, args2;
    va_start(args1, format);
    va_copy(args2, args1); // 复制一份 va_list

    // 第一次调用，获取需要的长度
    // 传入一个大小为0的缓冲区，snprintf不会写入任何东西，但会返回需要的长度
    int len = vsnprintf(NULL, 0, format, args1);
    va_end(args1);

    if (len < 0) {
        va_end(args2);
        return NULL; // 发生错误
    }

    // 分配足够的内存 (长度 + 1 个字节给 '\0')
    char* buffer = (char*)malloc(len + 1);
    if (!buffer) {
        va_end(args2);
        return NULL; // 内存分配失败
    }

    // 第二次调用，实际写入数据
    vsnprintf(buffer, len + 1, format, args2);
    va_end(args2);
    
    return buffer;
}

int main() {
    char* my_string = dynamic_format_string("Today is %s, %d, %d. The time is %02d:%02d.", 
                                            "August", 24, 2025, 10, 30);
    if (my_string) {
        printf("%s\n", my_string);
        free(my_string); // 不要忘记释放内存
    }

    return 0;
}

/*
总结与最佳实践

永远优先使用 snprintf 而不是 sprintf。这是C语言安全编程的黄金法则之一。

size 参数是关键：始终传递目标缓冲区的完整大小，例如使用 sizeof(buffer)。不要自己计算 size - 1，snprintf 会为你处理好 \0 的空间。

检查返回值：养成检查 snprintf 返回值的习惯。通过 if (ret >= size) 可以轻松判断是否发生了截断，这对于处理动态数据至关重要。

内存分配：如果你需要根据 snprintf 的返回值来动态分配内存，记得要分配 返回值 + 1 个字节，为 \0 留出空间。
*/
