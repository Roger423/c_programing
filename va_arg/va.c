
/*
C语言实现可变参数的函数。
C 语言中的 va_list、va_start、va_arg、va_end 和 va_copy 是一组宏，定义在头文件 <stdarg.h> 中，
用于实现 可变参数函数（variadic function），例如 printf。

🧠 一、概念理解
✅ 可变参数函数
允许函数接收可变数量的参数。

常见示例：printf, sprintf, fprintf, vprintf 等。

📚 二、每个宏的用途
-----------------------------------------------------------------------------------------------------------------
宏	                        说明
-----------------------------------------------------------------------------------------------------------------
va_list	                    声明一个变量，用于访问参数列表。
va_start(ap, last_param)	初始化 ap，指向参数列表中第一个可变参数，last_param 是最后一个固定参数。
va_arg(ap, type)	        访问当前参数，并将指针移向下一个参数。
va_end(ap)	                清理资源，结束参数访问。
va_copy(dest, src)	        复制参数访问指针，允许多个位置访问同一参数列表。
-----------------------------------------------------------------------------------------------------------------


🔧 三、使用方法（代码示例）
示例：实现一个简单的 my_sum(int count, ...)，求可变数量的整数和
*/

#include <stdio.h>
#include <stdarg.h>

int my_sum(int count, ...) {
    va_list args;
    int sum = 0;

    va_start(args, count); // 初始化 args，定位到第一个可变参数

    for (int i = 0; i < count; ++i) {
        int value = va_arg(args, int); // 读取下一个参数
        sum += value;
    }

    va_end(args); // 清理资源

    return sum;
}

int main() {
    printf("Sum = %d\n", my_sum(4, 10, 20, 30, 40)); // 输出：Sum = 100
    return 0;
}

/*
🧪 四、va_copy 的使用示例
当你要遍历参数两次时，需要复制 va_list，因为它本质上是一个遍历状态：


void print_twice(int count, ...) {
    va_list args1, args2;
    va_start(args1, count);
    va_copy(args2, args1);  // 复制一份参数列表

    printf("First pass:\n");
    for (int i = 0; i < count; ++i)
        printf(" %d", va_arg(args1, int));
    printf("\n");

    printf("Second pass:\n");
    for (int i = 0; i < count; ++i)
        printf(" %d", va_arg(args2, int));
    printf("\n");

    va_end(args1);
    va_end(args2);
}


⚠️ 五、使用注意事项
注意点	说明
类型必须准确	va_arg(args, type) 中的 type 必须和传入参数类型完全一致。
无法判断参数个数	可变参数本身无法确定数量，需使用固定参数如 count 或结束符（如 NULL）来判断终止。
不支持非 POD 类型（C++）	仅支持 int、double、char* 等基本类型或 POD 类型。
必须 va_end	否则可能造成资源泄露或未定义行为。
不支持默认参数类型提升	所有 char, short 会提升为 int，float 会提升为 double。

🔚 总结
宏	功能
va_list	声明参数访问对象
va_start(ap, last)	开始参数访问
va_arg(ap, type)	获取一个参数并前移
va_copy(dst, src)	复制参数访问状态
va_end(ap)	结束参数访问

这组宏是实现如日志打印、自定义格式输出、通用处理接口等功能的基础，尤其在嵌入式和底层系统开发中非常常见。需要严格遵循调用约定，确保类型匹配与生命周期管理。
*/
