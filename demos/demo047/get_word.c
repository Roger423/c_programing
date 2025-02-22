#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int get_word(char *buf, int buf_size, FILE *fp)
{
    int len, ch;

    // 跳过非字母数字字符，直到遇到一个字母或数字或EOF
    while ((ch = getc(fp)) != EOF && !isalnum(ch))
        ;
    
    if (ch == EOF)
        return EOF;
    
    len = 0;
    do {
        buf[len] = ch;
        len++;
        if (len >= buf_size) {
            fprintf(stderr, "Word too long.\n");
            exit(1);
        }
    } while ((ch = getc(fp)) != EOF && isalnum(ch));

    buf[len] = '\0';

    return len;
}

int main(void)
{
    char buf[256];
    int ch;

    while (1) {
        // 首先检查输入的第一个字符
        ch = getc(stdin);
        if (ch == EOF || ch == '#') {
            printf("Exiting...\n");
            break;
        }
        // 如果不是#，则回退字符以便get_word读取
        ungetc(ch, stdin);

        if (get_word(buf, 256, stdin) == EOF) {
            break;
        }
        printf("<<%s>>\n", buf);
    }

    return 0;
}
