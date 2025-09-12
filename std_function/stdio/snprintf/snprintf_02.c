
// 示例 2: 安全的字符串拼接 (替代 strcat)

#include <stdio.h>
#include <string.h>

int main() {
    char path[256];
    const char *base_dir = "/home/user";
    const char *filename = "document.txt";

    // 初始化缓冲区
    strncpy(path, base_dir, sizeof(path) - 1);
    path[sizeof(path) - 1] = '\0'; // 确保初始字符串是 null-terminated

    // 计算剩余空间和当前长度
    size_t current_len = strlen(path);
    size_t remaining_size = sizeof(path) - current_len;

    // 安全地追加
    snprintf(path + current_len, remaining_size, "/%s", filename);

    printf("完整路径: %s\n", path);

    return 0;
}
