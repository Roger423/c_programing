#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool find_sub_str_corrected(const char *src_str, const char *sub_str)
{
    // 1. 处理NULL输入，这是一种更安全的实践
    if (src_str == NULL || sub_str == NULL) {
        return false;
    }
    
    // 2. 如果子字符串是空字符串，按约定返回true
    if (*sub_str == '\0') {
        return true;
    }

    // 3. 主循环，src_str 在这里是外层循环的迭代器
    while (*src_str) {
        const char *p_src = src_str;  // 创建临时指针用于比较
        const char *p_sub = sub_str;

        // 4. 内层循环，用临时指针进行比较，不修改 src_str
        while (*p_src && *p_sub && *p_src == *p_sub) {
            p_src++;
            p_sub++;
        }

        // 5. 如果 p_sub 到达了末尾，说明所有字符都匹配了
        if (*p_sub == '\0') {
            return true;
        }

        // 6. 如果没有完全匹配，将 src_str 向前移动一个位置，进行下一次尝试
        src_str++;
    }

    // 7. 如果 src_str 遍历完了还没找到，返回 false
    return false;
}

int main()
{
    char *str1 = "abcdef";
    char *str2 = "abd";
    char *str3 = "cde";
    char *str4 = "";

    printf("Finding '%s' in '%s': %s\n", str2, str1, find_sub_str_corrected(str1, str2) ? "Yes" : "No"); // 应输出 No
    printf("Finding '%s' in '%s': %s\n", str3, str1, find_sub_str_corrected(str1, str3) ? "Yes" : "No"); // 应输出 Yes
    printf("Finding '%s' in '%s': %s\n", str4, str1, find_sub_str_corrected(str1, str4) ? "Yes" : "No"); // 应输出 Yes
}
