// 示例 3：完整的错误检查（推荐实践）
// 这是 strtoul 最强大和最安全的用法。

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>    // For errno
#include <limits.h>   // For ULONG_MAX

int main() {
    const char *test_strings[] = {
        "   12345",         // 正常
        "0xFFFFFFFF1",       // 溢出
        "123.45",          // 有效数字后跟无效字符
        "Hello World",       // 无效字符串
        ""                 // 空字符串
    };

    for (int i = 0; i < 5; ++i) {
        const char *str = test_strings[i];
        char *endptr;

        // 在调用前必须重置 errno
        errno = 0;

        unsigned long val = strtoul(str, &endptr, 0);

        printf("Original string: \"%s\"\n", str);

        // 检查溢出
        if (errno == ERANGE) {
            printf(" -> Error: Number out of range for unsigned long.\n\n");
            continue;
        }

        // 检查是否发生转换
        if (endptr == str) {
            printf(" -> Error: No valid digits were found for conversion.\n\n");
            continue;
        }

        // 检查是否有未转换的后缀
        if (*endptr != '\0') {
            printf(" -> Value: %lu. Conversion stopped at: \"%s\"\n\n", val, endptr);
        } else {
            printf(" -> Value: %lu. Conversion successful.\n\n", val);
        }
    }

    return 0;
}
// 输出：
// Original string: "   12345"
//  -> Value: 12345. Conversion successful.
// 
// Original string: "0xFFFFFFFF1"
//  -> Error: Number out of range for unsigned long.
// 
// Original string: "123.45"
//  -> Value: 123. Conversion stopped at: ".45"
// 
// Original string: "Hello World"
//  -> Error: No valid digits were found for conversion.
// 
// Original string: ""
//  -> Error: No valid digits were found for conversion.
