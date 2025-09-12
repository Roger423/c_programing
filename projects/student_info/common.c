#include "common.h"


/**
 * @brief 从指定的流中安全地读取一行，并移除末尾的换行符。
 * @param dst   用于存储输入字符串的目标缓冲区。
 * @param size  目标缓冲区的完整大小。
 * @param stream 输入流 (例如 stdin)。
 * @return int   成功返回 0, 遇到文件结尾或错误返回 EOF。
 */
int get_input_line(char *dst, size_t size, FILE *stream)
{
    if (fgets(dst, size, stream) == NULL) {
        return EOF;
    }

    // 检查是否需要清理缓冲区
    // 如果字符串中没有换行符，并且缓冲区不是因为EOF而停止读取
    // 这就意味着输入行太长了，缓冲区里装满了，但行还没结束
    if (strchr(dst, '\n') == NULL && !feof(stream)) {
        int c;
        // 清理掉输入流中直到下一个换行符或文件结尾的所有字符
        while ((c = fgetc(stream)) != '\n' && c != EOF);
    }
    
    // 移除末尾的换行符
    dst[strcspn(dst, "\n")] = '\0';

    return 0; // 成功
}
