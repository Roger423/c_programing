#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 辅助函数：将单个十六进制字符转换为数值
static int hex_char_to_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // 表示无效字符
}

/**
 * @brief 直接解析包含各种分隔符或无分隔符的MAC地址字符串。
 */
int mac_str_to_bin(const char *str, unsigned char *mac) {
    const char *p = str;
    int val1, val2;

    if (str == NULL || mac == NULL) {
        return -1;
    }

    for (int i = 0; i < 6; i++) {
        // 寻找第一个有效的十六进制字符
        while (*p && !isxdigit(*p)) p++;
        if (!*p) return -1; // 如果没找到就结束了，说明字符串格式错误
        val1 = hex_char_to_value(*p++);

        // 寻找第二个有效的十六进制字符
        while (*p && !isxdigit(*p)) p++;
        if (!*p) return -1;
        val2 = hex_char_to_value(*p++);
        
        // 合并两个半字节为一个字节
        mac[i] = (unsigned char)((val1 << 4) | val2);
    }
    
    return 0;
}

// --- 测试代码 ---
void print_mac(unsigned char *mac) {
    for (int i = 0; i < 6; i++) {
        printf("%02x%s", mac[i], (i < 5) ? ":" : "");
    }
    printf("\n");
}

int main() {
    // 准备不同格式的MAC地址字符串
    const char *mac_str1 = "00:aa:11:bb:22:cc";
    const char *mac_str2 = "00-aa-11-bb-22-cc";
    const char *mac_str3 = "00aa11bb22cc";
    const char *mac_str4 = "00 aa 11 bb 22 cc"; // 带空格
    const char *mac_str5 = "00:aa-11 bb.22 cc"; // 混合分隔符
    const char *mac_str6 = "00aa:11bb:22cc";
    
    unsigned char mac_arr[6];

    printf("Parsing '%s':\t", mac_str1);
    if (mac_str_to_bin(mac_str1, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");

    printf("Parsing '%s':\t", mac_str2);
    if (mac_str_to_bin(mac_str2, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");

    printf("Parsing '%s':\t", mac_str3);
    if (mac_str_to_bin(mac_str3, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");

    printf("Parsing '%s':\t", mac_str4);
    if (mac_str_to_bin(mac_str4, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");

    printf("Parsing '%s':\t", mac_str5);
    if (mac_str_to_bin(mac_str5, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");

    printf("Parsing '%s':\t", mac_str6);
    if (mac_str_to_bin(mac_str6, mac_arr) == 0) print_mac(mac_arr); else printf("Failed\n");
    
    return 0;
}
