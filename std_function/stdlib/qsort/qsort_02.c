
//(2) 排序字符串数组（按字典序）

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_str(const void *a, const void *b) {
    const char *sa = *(const char **)a;
    const char *sb = *(const char **)b;
    return strcmp(sa, sb);
}

int main() {
    const char *words[] = {"pear", "apple", "orange", "banana"};
    int n = sizeof(words) / sizeof(words[0]);

    qsort(words, n, sizeof(char *), cmp_str);

    printf("排序结果: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", words[i]);
    }
    return 0;
}

