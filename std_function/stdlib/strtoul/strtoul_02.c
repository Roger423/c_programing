//示例 2：使用 base = 0 自动检测进制

#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *hex_str = "0x1A"; // 1*16 + 10 = 26
    const char *oct_str = "077";  // 7*8 + 7 = 63
    const char *dec_str = "42";   // 42

    unsigned long hex_val = strtoul(hex_str, NULL, 0);
    unsigned long oct_val = strtoul(oct_str, NULL, 0);
    unsigned long dec_val = strtoul(dec_str, NULL, 0);

    printf("'%s' is %lu\n", hex_str, hex_val);
    printf("'%s' is %lu\n", oct_str, oct_val);
    printf("'%s' is %lu\n", dec_str, dec_val);

    return 0;
}
// 输出：
// '0x1A' is 26
// '077' is 63
// '42' is 42


