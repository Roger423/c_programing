#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // 需要包含 ctype.h 用于 isxdigit

/**
 * @brief 将包含各种分隔符或无分隔符的MAC地址字符串转换为二进制数组。
 * * @param str 输入的MAC地址字符串。支持 "00:aa:11:bb:22:cc", 
 * "00-aa-11-bb-22-cc", "00aa11bb22cc" 等格式。
 * @param mac 指向6字节无符号字符数组的指针，用于存储结果。
 * @return 成功返回0，失败返回-1。
 */
int mac_str_to_bin(const char *str, unsigned char *mac) {
    char sanitized_mac[13]; // 存储12个十六进制字符 + 1个结尾符'\0'
    int count = 0;
    char byte_str[3]; // 用于临时存放2个十六进制字符

    if (str == NULL || mac == NULL) {
        return -1;
    }

    // 1. 净化字符串：遍历输入字符串，只保留十六进制字符
    for (int i = 0; str[i] != '\0' && count < 12; i++) {
        if (isxdigit(str[i])) { // isxdigit 检查字符是否为十六进制数字 (0-9, a-f, A-F)
            sanitized_mac[count++] = str[i];
        }
    }
    sanitized_mac[count] = '\0'; // 添加字符串结尾

    // 2. 验证净化后的长度是否正确
    if (count != 12) {
        // 如果没有找到12个十六进制数字，则格式错误
        return -1; 
    }

    // 3. 解析净化后的字符串，两个字符一组
    for (int i = 0; i < 6; i++) {
        // 从净化后的字符串中取出两个字符
        byte_str[0] = sanitized_mac[i * 2];
        byte_str[1] = sanitized_mac[i * 2 + 1];
        byte_str[2] = '\0'; // 形成一个2字符的短字符串

        // 使用 strtoul 将这两个字符转换为一个字节
        mac[i] = (unsigned char)strtoul(byte_str, NULL, 16);
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
