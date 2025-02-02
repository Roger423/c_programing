//compile cmd:  gcc -std=c11 -pthread -o multithrd multithrd.c

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

// 线程函数
int threadFunc(void* arg) {
    int num = *(int*)arg;
    printf("线程 %d 正在运行\n", num);
    return 0;
}

int main() {
    thrd_t threads[3];
    int thread_nums[3];

    // 创建3个线程
    for (int i = 0; i < 3; i++) {
        thread_nums[i] = i + 1;
        if (thrd_create(&threads[i], threadFunc, &thread_nums[i]) != thrd_success) {
            fprintf(stderr, "创建线程 %d 失败\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // 等待线程结束
    for (int i = 0; i < 3; i++) {
        thrd_join(threads[i], NULL);
    }

    printf("所有线程已结束\n");
    return 0;
}
