#include <stdio.h>
#include <string.h>

int main() {
    char str[20] = "abcdefghij";

    printf("原始字符串: %s\n", str);

    // 将 str 地址开始的 5 个字节 ("abcde") 移动到 str+2 地址
    // dest > src，如果使用 memcpy，'a' 拷贝到 'c'，'b' 拷贝到 'd'，
    // 但当准备拷贝 'c' 时，原来的 'c' 已经被 'a' 覆盖了，导致错误。
    // memmove 会从后往前拷贝，保证正确性。
    memmove(str + 2, str, 5);

    printf("移动后字符串: %s\n", str);

    return 0;
}

/*
输出:

原始字符串: abcdefghij
移动后字符串: ababcdehij


说明：memmove 正确地处理了重叠，将 "abcde" 插入到了原 "c" 的位置。如果这里使用 memcpy，结果可能是 "ab" 被重复拷贝，
导致 "ababab..." 这样的错误结果。

*/