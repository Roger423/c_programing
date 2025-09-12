#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 5
#define ELEM_PER_LINE 8
#define MAX_INT 99

typedef struct {
    int *elem;
    int length;
    int list_size;
} sq_list;

void print_list(sq_list *slist);
int is_full(sq_list *slist);
int extend(sq_list *slist);
int insert(sq_list *slist, int pos, int elem);
int search(sq_list *slist, int elem);
int delete_by_position(sq_list *slist, int pos);
int delete_by_element(sq_list *slist, int elem);

int main(void) {
    sq_list slist;
    slist.elem = malloc(LIST_INIT_SIZE * sizeof(int));
    if (!slist.elem) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    slist.length = 0;
    slist.list_size = LIST_INIT_SIZE;

    srand((unsigned)time(NULL));
    for (int i = 0; i < 15; ++i) {
        insert(&slist, i, rand() % (MAX_INT + 1));
    }

    print_list(&slist);

    delete_by_position(&slist, 0);
    delete_by_position(&slist, 2);
    delete_by_position(&slist, 6);  // 注意：删除前应确保 index 有效
    delete_by_position(&slist, 11); // 可能越界，忽略失败返回值

    print_list(&slist);

    delete_by_element(&slist, 100); // 测试找不到元素的情况
    delete_by_element(&slist, slist.elem[0]); // 测试找到元素的情况

    print_list(&slist);

    free(slist.elem);
    return 0;
}

void print_list(sq_list *slist) {
    printf("All elements of list:\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < slist->length; i++) {
        if (i > 0 && i % ELEM_PER_LINE == 0)
            printf("\n");
        printf("%-6d", slist->elem[i]);
    }
    printf("\n------------------------------------------------\n");
}

int is_full(sq_list *slist) {
    return slist->length == slist->list_size;
}

int extend(sq_list *slist) {
    int new_size = slist->list_size + LIST_INCREMENT;
    int *new_list = realloc(slist->elem, new_size * sizeof(int));
    if (!new_list) {
        fprintf(stderr, "realloc failed during extend!\n");
        return -1;
    }
    slist->elem = new_list;
    slist->list_size = new_size;
    return 0;
}

int insert(sq_list *slist, int insert_pos, int insert_elem) {
    if (insert_pos < 0 || insert_pos > slist->length) {
        fprintf(stderr, "Invalid insert position: %d\n", insert_pos);
        return -1;
    }

    if (is_full(slist)) {
        if (extend(slist) != 0) return -1;
    }

    for (int i = slist->length; i > insert_pos; i--) {
        slist->elem[i] = slist->elem[i - 1];
    }

    slist->elem[insert_pos] = insert_elem;
    slist->length++;
    return 0;
}

int search(sq_list *slist, int elem) {
    for (int i = 0; i < slist->length; i++) {
        if (slist->elem[i] == elem)
            return i;
    }
    return -1;
}

int delete_by_position(sq_list *slist, int pos) {
    if (pos < 0 || pos >= slist->length) {
        fprintf(stderr, "Invalid delete position: %d\n", pos);
        return -1;
    }

    for (int i = pos; i < slist->length - 1; i++) {
        slist->elem[i] = slist->elem[i + 1];
    }

    slist->length--;
    return 0;
}

int delete_by_element(sq_list *slist, int elem) {
    int pos = search(slist, elem);
    if (pos == -1) {
        fprintf(stderr, "Element %d not found.\n", elem);
        return -1;
    }

    while (pos != -1) {
        delete_by_position(slist, pos);
        pos = search(slist, elem);
    }

    return 0;
}
