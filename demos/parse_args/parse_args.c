#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CLI_CMD_ARGS_NUM_MAX 8
#define CLI_CMD_LINE_CHAR_MAX 64

int parse_input_line(char *line, char *argv[], int max_args)
{
    int argc = 0;
    char *p = line;

    while (*p && argc < max_args) {
        // 跳过开头的空格
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') break;

        // 如果是引号开头，支持带空格的参数
        if (*p == '"') {
            p++;
            argv[argc++] = p;
            while (*p && *p != '"') {
                p++;
            }
            if (*p == '"') {
                *p++ = '\0';
            }
        }
        else {
            argv[argc++] = p;
            while (*p && !isspace((unsigned char)*p)) {
                p++;
            }
            if (*p) {
                *p++ = '\0';
            }
        }
    }

    return argc;
}

int main()
{
    char line[CLI_CMD_LINE_CHAR_MAX] = "set_ip  \"192.168.1.100 255.255.255.0\" eth0";
    char *argv[CLI_CMD_ARGS_NUM_MAX];
    int argc, i;

    argc = parse_input_line(line, argv, CLI_CMD_ARGS_NUM_MAX);

    printf("argc = %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("argv[%d] = [%s]\n", i, argv[i]);
    }

    return 0;
}
