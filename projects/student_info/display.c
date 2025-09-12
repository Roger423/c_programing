#include <termios.h>
#include <unistd.h>
#include "display.h"


static struct termios orig_termios;

static void restore_terminal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

/* 把终端设置为非规范（即时）模式并关闭回显。
 * vmin/vtime 控制 read() 的行为：VTIME 单位是 1/10 秒。
 * 推荐：VMIN = 0, VTIME = 1 -> read 最多等 0.1s，返回已到达的字节（也可能为 0）
 */
static int set_input_mode(int vmin, int vtime) {
    struct termios t;

    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) return -1;
    atexit(restore_terminal); // 程序退出时自动恢复

    t = orig_termios;

    // 关闭规范模式和回显
    t.c_lflag &= ~(ICANON | ECHO);

    // 保留 ISIG（Ctrl-C 等仍然有效）：
    // 若想禁用信号，请 also remove ISIG，但通常不建议这样做
    // t.c_lflag &= ~ISIG;

    // 输入处理：关闭 CR->NL 映射和软件流控
    t.c_iflag &= ~(ICRNL | IXON);

    // 输出处理：通常关闭 OPOST（输出后处理），便于控制转义序列行为一致
    t.c_oflag &= ~(OPOST);

    // 控制字符
    t.c_cc[VMIN] = vmin;
    t.c_cc[VTIME] = vtime;

    // 立刻生效
    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1) return -1;
    return 0;
}

static void reset_input_mode(void) {
    restore_terminal();

    // 清理输入缓冲区，避免残余影响 fgets()
    tcflush(STDIN_FILENO, TCIFLUSH);
}

void print_student_info(student_info *stu_info)
{
    printf("Student ID       : %s\n\r", stu_info->id);
    printf("Student Name     : %s\n\r", stu_info->name);
    printf("Student Gender   : %s\n\r", stu_info->gender);
    printf("Student Age      : %hu\n\r", stu_info->age);
    printf("Student Phone No.: %s\n\r", stu_info->phone_num);
    printf("Student Address  : %s\n\n\r", stu_info->address);
}

static void print_page_student_info(students *stus, int page_num, int page_size, int total_page)
{
    printf("\x1b[2J\x1b[H");
    int start_idx = (page_num - 1) * page_size;
    int end_idx = start_idx + page_size;
    if (end_idx > stus->stu_num) end_idx = stus->stu_num;
    printf("%s\n\r", SPLIT_LINE);
    printf("Students information of page No.%d(Total pages: %d):\n\n\r", page_num, total_page);
    for (int i = start_idx; i < end_idx; i++) {
        print_student_info(&stus->student_list[i]);
    }
    printf("%s\n\r", SPLIT_LINE);
    printf("Press ↑ (Previous Page) | ↓ (Next Page) | Q (quit)\n\r");
    printf("%s\n\r", SPLIT_LINE);
}

void show_all_students_info(students *stus)
{
    if (stus->stu_num == 0) {
        printf("\n\n%s\n", SPLIT_LINE);
        printf("No students info in system\n");
        printf("\n\n%s\n", SPLIT_LINE);
        return;
    }
    printf("\n\n%s\n", SPLIT_LINE);
    printf("To display all students information.\n");
    printf("Please input how many students information to display in one page: \n");
    printf("Number per page(1-50):");
    char num_per_page_str[16];
    get_input_line(num_per_page_str, sizeof(num_per_page_str), stdin);
    unsigned int num_per_page = (unsigned int)strtoul(num_per_page_str, NULL, 10);
    if (num_per_page == 0 || num_per_page > 50) {
        printf("Invalid input, set number per page to default value: %d", DEFAULT_STUDENT_INFO_NUM_PER_PAGE);
        num_per_page = DEFAULT_STUDENT_INFO_NUM_PER_PAGE;
    }

    int total_page_num = (stus->stu_num + num_per_page - 1) / num_per_page;
    if (total_page_num == 0) total_page_num = 1;
    int current_page = 1;
    printf("%s\n\n", SPLIT_LINE);
    printf("All students information:\n");

    print_page_student_info(stus, current_page, num_per_page, total_page_num);

    if (set_input_mode(0, 1) < 0) {
        fprintf(stderr, "Set input mode ERROR!");
        return;
    }

    unsigned char buf[16];
    int read_size;

    while (true) {
        read_size = read(STDIN_FILENO, buf, sizeof(buf));
        if (read_size > 0) {
            if (buf[0] == 27 && buf[1] == '[') {
                if (buf[2] == 'A') {
                    if (current_page > 1) {
                        current_page--;
                        print_page_student_info(stus, current_page, num_per_page, total_page_num);
                    }
                }
                else if (buf[2] == 'B') {
                    if (current_page < total_page_num) {
                        current_page++;
                        print_page_student_info(stus, current_page, num_per_page, total_page_num);
                    }
                }
            }
            else if (buf[0] == 'q' || buf[0] == 'Q') {
                break;
            }
        }
    }
    reset_input_mode();
}
