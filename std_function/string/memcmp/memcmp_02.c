/*
使用 memcmp 比较结构体是一个非常常见且高效的操作，但需要特别注意一个陷阱：结构体填充（Padding）。

下面我将通过一个例子来展示如何正确地比较结构体，并解释这个陷阱。

💡 基本思路
如果两个结构体变量的内存映像（memory footprint）完全一样，那么它们就是相等的。memcmp 正是用来比较内存映像的。

我们将定义一个 Player 结构体，并创建几个实例来进行比较。
*/

//代码示例

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // 为了 memset

// 定义一个玩家结构体
typedef struct {
    int id;
    char name[20];
    double score;
} Player;

void print_player(const Player* p) {
    printf("ID: %d, Name: %s, Score: %.2f\n", p->id, p->name, p->score);
}

int main() {
    Player p1, p2, p3;

    // --- 使用前，先将结构体内存清零 ---
    // 这是最关键的一步，可以确保所有字节（包括填充字节）都被设置为0
    memset(&p1, 0, sizeof(Player));
    memset(&p2, 0, sizeof(Player));
    memset(&p3, 0, sizeof(Player));


    // --- 场景1: 比较两个完全相同的结构体 ---
    // 初始化玩家1
    p1.id = 101;
    strcpy(p1.name, "Alice");
    p1.score = 95.5;

    // 初始化玩家2，使其与玩家1内容完全相同
    p2.id = 101;
    strcpy(p2.name, "Alice");
    p2.score = 95.5;

    printf("玩家1信息: ");
    print_player(&p1);
    printf("玩家2信息: ");
    print_player(&p2);

    // 使用 memcmp 比较 p1 和 p2 的内存
    if (memcmp(&p1, &p2, sizeof(Player)) == 0) {
        printf("✅ 比较结果: 玩家1 和 玩家2 的内容完全相同。\n\n");
    } else {
        printf("❌ 比较结果: 玩家1 和 玩家2 的内容不相同。\n\n");
    }


    // --- 场景2: 比较两个内容不同的结构体 ---
    // 初始化玩家3，使其与玩家1略有不同
    p3.id = 101;
    strcpy(p3.name, "Alice");
    p3.score = 99.0; // 分数不同

    printf("玩家1信息: ");
    print_player(&p1);
    printf("玩家3信息: ");
    print_player(&p3);

    // 使用 memcmp 比较 p1 和 p3 的内存
    if (memcmp(&p1, &p3, sizeof(Player)) == 0) {
        printf("✅ 比较结果: 玩家1 和 玩家3 的内容完全相同。\n");
    } else {
        printf("❌ 比较结果: 玩家1 和 玩家3 的内容不相同。\n");
    }

    return 0;
}

/*
预期输出:

玩家1信息: ID: 101, Name: Alice, Score: 95.50
玩家2信息: ID: 101, Name: Alice, Score: 95.50
✅ 比较结果: 玩家1 和 玩家2 的内容完全相同。

玩家1信息: ID: 101, Name: Alice, Score: 95.50
玩家3信息: ID: 101, Name: Alice, Score: 99.00
❌ 比较结果: 玩家1 和 玩家3 的内容不相同。
*/

/*
⚠️ 注意：结构体填充（Padding）问题
上面的例子能够正确工作，是因为我们使用了 memset。如果不使用 memset，memcmp 的结果可能是不可预测的。

为什么？

编译器为了提高CPU访问内存的效率，会在结构体的成员之间或末尾添加一些填充字节（Padding Bytes）。

例如，对于我们的 Player 结构体，它在内存中可能看起来是这样的：
| int id (4字节) | char name[20] (20字节) | ??? (4字节填充) | double score (8字节) |

编译器可能会在 name 和 score 之间插入4个填充字节，以确保 score (一个 double 类型) 从一个能被8整除的地址开始，这样访问速度最快。

关键问题是： 这些填充字节里的值是未定义的（可能是随机的垃圾值）。

如果你不使用 memset 清零，即使两个结构体的所有成员（id, name, score）都完全一样，它们的填充字节也可能不一样。这样一来，
memcmp 在进行逐字节比较时，就会在填充字节处发现差异，从而错误地报告两个结构体不相等。

最佳实践：
在使用 memcmp 比较结构体之前，养成用 memset 将其内存区域完全清零的好习惯。

Player my_player;
memset(&my_player, 0, sizeof(Player));
// 然后再给成员赋值
my_player.id = ...;

-----------------------------------------------------------------------------------------------
替代方案：逐成员比较
如果你想避免处理填充字节问题，或者想让比较逻辑更清晰，可以编写一个专门的函数来逐个比较结构体的成员。

#include <stdbool.h> // 为了使用 bool 类型

// 返回 true 表示相等, false 表示不相等
bool compare_players(const Player* p1, const Player* p2) {
    if (p1->id != p2->id) {
        return false;
    }
    if (strcmp(p1->name, p2->name) != 0) {
        return false;
    }
    // 对于浮点数，直接用 == 比较可能因精度问题出错，最好是检查差的绝对值
    if (fabs(p1->score - p2->score) > 0.001) { // fabs 在 <math.h> 中
        return false;
    }
    return true; // 所有成员都相等
}

对比两种方法：

memcmp + memset

优点：代码简洁，执行效率通常非常高。

缺点：必须记住要 memset，否则会因填充字节而出错。

逐成员比较函数

优点：代码逻辑清晰，完全不受填充字节影响，绝对安全。可以自定义浮点数的比较精度。

缺点：代码更冗长，对于有大量成员的结构体，可能会稍微慢一点点（通常可忽略不计）。

在追求极致性能的底层代码或网络编程中，memcmp 很常用。在普通的应用程序中，编写一个独立的比较函数通常是更安全、更易维护的选择。

*/