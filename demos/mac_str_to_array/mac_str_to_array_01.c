#include <stdio.h>
#include <stdlib.h>

int mac_str_to_bin(const char *str, unsigned char *mac) {
    int i;
    char *s, *e = NULL;

    if ((mac == NULL) || (str == NULL)) {
        return -1;
    }

    s = (char *)str;
    for (i = 0; i < 6; ++i) {
        mac[i] = s? strtoul(s, &e, 16) : 0;
        if (s)
            s = (*e)? e + 1 : e;
    }

    return 0;
}

int main()
{
    char mac_str[] = "00:aa:11:bb:22:cc";
    unsigned char mac_arr[6] = {0};
    printf("MAC str: %s\n", mac_str);
    mac_str_to_bin(mac_str, mac_arr);
    for(int i = 0; i < 6; i++){
        printf("MAC array [%d]: %02x\n", i, mac_arr[i]);
    }
}
