#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 20

int read_line(char str[], int n);
int compare_words(const void *a, const void *b);

int main(void) {
    char *words[100];
    char word[MAX_WORD_LEN + 1];
    int count = 0;

    while (1) {
        printf("Enter word: ");
        read_line(word, MAX_WORD_LEN);

        if (strlen(word) == 0) {
            break;
        }

        words[count] = malloc(strlen(word) + 1);
        if (words[count] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy(words[count], word);
        count++;
    }

    // 使用qsort对单词进行排序
    qsort(words, count, sizeof(char *), compare_words);

    // 打印排序后的单词
    printf("\nIn sorted order:");
    for (int i = 0; i < count; i++) {
        printf(" %s", words[i]);
        free(words[i]);
    }
    printf("\n");

    return 0;
}

int read_line(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}

int compare_words(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
