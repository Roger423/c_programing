#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool find_sub_str(const char *src_str, const char *sub_str) {
    if (src_str == NULL || sub_str == NULL) return false;
    if (*sub_str == '\0') return true;  // 修复空字符串检查

    int sub_str_len = strlen(sub_str);
    int src_str_len = strlen(src_str);  // 缓存长度
    if (sub_str_len > src_str_len) return false;

    char sub_str_first_char = *sub_str;

    for (int i = 0; i <= src_str_len - sub_str_len; i++) {
        if (src_str[i] != sub_str_first_char) continue;
        bool match = true;
        for (int j = 1; j < sub_str_len; j++) {
            if (src_str[i + j] != sub_str[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

int main() {
    char *str1 = "abcdef";
    char *str2 = "abd";

    bool sub_str_find = find_sub_str(str1, str2);
    printf("%s\n", sub_str_find ? "Yes" : "No");

    // 额外测试用例
    printf("Test 'abc': %s\n", find_sub_str("abcdef", "abc") ? "Yes" : "No");
    printf("Test '': %s\n", find_sub_str("abcdef", "") ? "Yes" : "No");
    printf("Test 'c': %s\n", find_sub_str("abcdef", "c") ? "Yes" : "No");
    return 0;
}
