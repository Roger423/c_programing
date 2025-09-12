/*
一、函数原型

int fprintf(FILE *stream, const char *format, ...);

FILE *stream：目标输出流，决定输出到哪里。常见的有：

stdout → 标准输出（通常是屏幕/终端）

stderr → 标准错误输出

fopen() 打开的文件指针 → 输出到文件

const char *format：格式化字符串，跟 printf 一样，包含普通字符和格式说明符（%d、%s 等）。

...：可变参数，对应格式化字符串里的说明符。

返回值：成功时返回打印的字符数，失败时返回负值。

---------------------------------------------------
二、常用格式说明符

和 printf 相同：

---------------------------------------------------
格式	说明	                        示例
---------------------------------------------------
%d	    输出 int 类型（十进制）	         42
%u	    无符号十进制	                100
%x/%X	十六进制（小写/大写）	         2a / 2A
%f	    浮点数（小数点）	             3.14
%c	    字符	                        A
%s	    字符串	                        hello
%p	    指针地址	                    0x7ff...
---------------------------------------------------
还可以加宽度和精度控制，比如：

%5d → 输出宽度至少 5，右对齐
%-5d → 宽度 5，左对齐
%.2f → 输出小数点后 2 位
*/

#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    fprintf(fp, "Hello, %s! Your score is %d.\n", "Alice", 95);

    fclose(fp);
    return 0;
}

/*
👉 会在 output.txt 文件里写入：
Hello, Alice! Your score is 95.

*/

/*
2. 输出到标准输出
fprintf(stdout, "This goes to screen: %d\n", 123);

等价于：
printf("This goes to screen: %d\n", 123);


3. 输出到标准错误
fprintf(stderr, "Error: invalid input '%s'\n", input_str);
👉 常用于打印错误日志。


四、和其他函数的关系

printf → fprintf(stdout, ...) 的简写。
sprintf → 把结果写入字符串，而不是输出流。
snprintf → 把结果写入字符串，限制最大长度，防止溢出。
dprintf → 输出到文件描述符（Unix/Linux 专用，底层 fd，而不是 FILE*）。

五、注意事项

文件必须打开成功（fopen 返回非 NULL），否则 fprintf 会失败。
缓冲问题：
stdout 通常是行缓冲（换行时才真正写出）。
stderr 默认无缓冲（立即写出）。
可以用 fflush(fp) 强制刷新。
返回值检查：如果 fprintf 返回负值，说明写入失败（可能是磁盘满了、文件权限不足等）。
安全问题：fprintf(fp, str) 里如果 str 是用户输入，可能会被当作格式化字符串执行 → 建议写 fprintf(fp, "%s", str);。
*/

