/*
2. 重叠内存区域拷贝（memmove 的威力所在）
这是 memmove 最重要的应用场景。假设我们想将一个字符串的一部分向前或向后移动，这时源和目标内存区域就会重叠。

示例：将字符串的一部分向前移动

假设我们有一个字符串 [a][b][c][d][e][f]，我们想把从 [c] 开始的 4 个字节 [c][d][e][f] 移动到从 [a] 开始的位置。

源（src）：&str[2] (指向 'c')

目标（dest）：&str[0] (指向 'a')

重叠情况：目标地址在源地址之前。
*/

#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "abcdefghij";

    printf("原始字符串: %s\n", str);

    // 将 str+2 地址开始的 5 个字节 ("cdefg") 移动到 str 地址
    // dest < src，从前往后拷贝是安全的
    memmove(str, str + 2, 5);

    printf("移动后字符串: %s\n", str);

    return 0;
}

// 输出:

// 原始字符串: abcdefghij
// 移动后字符串: cdefgefghij


/*
说明：memmove 成功地将 "cdefg" 移动到了字符串的开头，覆盖了原来的 "ab"。

示例：将字符串的一部分向后移动

假设我们有一个字符串 [a][b][c][d][e][f]，我们想把从 [a] 开始的 4 个字节 [a][b][c][d] 移动到从 [c] 开始的位置。

源（src）：&str[0] (指向 'a')

目标（dest）：&str[2] (指向 'c')

重叠情况：目标地址在源地址之后。


*/