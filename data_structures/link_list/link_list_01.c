
#include <stdio.h>
#include <stdlib.h>


struct node_info {
    int value;
    struct node_info *next;
};

struct found_info {
    unsigned int found_count;
    unsigned int found_index_list[];
};


int init_link_list(struct node_info *list_head, int value_list[], int value_count)
{
    if (list_head == NULL || value_count <= 0) return -1;
    struct node_info *p = list_head;

    for (int i = 0; i < value_count; i++) {
        struct node_info *new_node = malloc(sizeof(struct node_info));
        if (!new_node) {
            printf("Alloc memory for new node failed!\n");
            return -1;
        }
        new_node->value = value_list[i];
        new_node->next = NULL;
        p->next = new_node;
        p = new_node;
    }
    return 0;
}

void free_link_list(struct node_info *list_head)
{
    if (list_head == NULL) return;
    struct node_info *current = list_head->next, *next_node;
    while (current) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    list_head->next = NULL;
}

void display_link_list(struct node_info *list_head)
{
    struct node_info *p = list_head->next;
    unsigned int idx = 0;
    while (p) {
        printf("Node value of index %u: %d\n", idx, p->value);
        p = p->next;
        idx++;
    }
}

struct found_info* find(struct node_info *list_head, int find_value)
{
    if (list_head == NULL) return NULL;

    unsigned int found_count = 0;
    struct node_info *p = list_head->next;
    while(p) {
        if (p->value == find_value) found_count++;
        p = p->next;
    }

    struct found_info *fd_info = NULL;
    if (found_count > 0) {
        fd_info = malloc(sizeof(struct found_info) + found_count * sizeof(unsigned int));
        if (!fd_info) {
            printf("Alloc memory for found_info failed!\n");
            return NULL;
        }
        fd_info->found_count = found_count;
    } else {
        return NULL;
    }

    unsigned int link_list_idx = 0;
    unsigned int found_list_idx = 0; 
    p = list_head->next;
    while(p) {
        if (p->value == find_value) {
            if (found_list_idx < found_count) {
                fd_info->found_index_list[found_list_idx] = link_list_idx;
                found_list_idx++;
            }
        }
        p = p->next;
        link_list_idx++;
    }

    return fd_info;
}

/*
find函数的另一个版本，不需要两次遍历。使用动态变化大小数组。
struct found_info* find(struct node_info *list_head, int find_value)
{
    if (!list_head) return NULL;

    unsigned int cap = 4;   // 初始容量
    unsigned int count = 0;
    struct found_info *fd_info = malloc(sizeof(struct found_info) + cap * sizeof(unsigned int));
    if (!fd_info) return NULL;

    struct node_info *p = list_head->next;
    unsigned int idx = 0;

    while (p) {
        if (p->value == find_value) {
            if (count >= cap) {
                cap *= 2;
                struct found_info *new_fd = realloc(fd_info, sizeof(struct found_info) + cap * sizeof(unsigned int));
                if (!new_fd) {
                    free(fd_info);
                    return NULL;
                }
                fd_info = new_fd;
            }
            fd_info->found_index_list[count++] = idx;
        }
        idx++;
        p = p->next;
    }

    if (count == 0) {
        free(fd_info);
        return NULL;
    }

    fd_info->found_count = count;

    // 可选：再收缩一次，节省内存
    struct found_info *shrink_fd = realloc(fd_info, sizeof(struct found_info) + count * sizeof(unsigned int));
    return shrink_fd ? shrink_fd : fd_info;
}
*/

int insert(struct node_info *list_head, int insert_value, unsigned int insert_pos)
{
    struct node_info *new_node = malloc(sizeof(struct node_info));
    if (!new_node) {
        printf("Alloc memory for insert node failed.\n");
        return -1;
    }
    new_node->value = insert_value;
    struct node_info *p = list_head;
    for (unsigned int i = 0; i < insert_pos; i++) {
        p = p->next;
        if (p == NULL) {
            printf("Insert position out of link list range.\n");
            free(new_node);
            return -1;
        }
    }

    new_node->next = p->next;
    p->next = new_node;

    return 0;
}

int delete(struct node_info *list_head, unsigned int del_pos)
{
    struct node_info *p = list_head;
    for (unsigned int i = 0; i < del_pos; i++) {
        p = p->next;
        if (!p) {
            printf("Delete position out of link list range.\n");
            return -1;
        }
    }

    if (p->next == NULL) {
        printf("Delete position out of link list range.\n");
        return -1;
    }

    struct node_info *del_node = p->next;
    p->next = del_node->next;
    free(del_node);

    return 0;
}

int main()
{
    // 使用头节点可以简化插入和删除操作
    struct node_info link_list = {.value = 0, .next = NULL};
    int init_list[] = {1, 2, 3, 4, 5};

    if (init_link_list(&link_list, init_list, 5) < 0) {
        printf("Initiate link list failed\n");
        return -1;
    }
    printf("--- Initial List ---\n");
    display_link_list(&link_list);

    printf("--- After inserting 10 at pos 0 ---\n");
    if (insert(&link_list, 10, 0) < 0) {
        printf("Insert failed!\n");
    } else {
        display_link_list(&link_list);
    }

    printf("--- After inserting 20 at pos 2 ---\n");
    if (insert(&link_list, 20, 2) < 0) {
        printf("Insert failed!\n");
    } else {
        display_link_list(&link_list);
    }
    
    // 尝试一个会失败的插入
    printf("--- Trying to insert 99 at pos 10 (out of bounds) ---\n");
    if (insert(&link_list, 99, 10) < 0) {
        printf("Insert failed as expected.\n");
    }
    display_link_list(&link_list);

    printf("--- Insert a existing value 5 at pos 1 ---\n");
    if (insert(&link_list, 5, 1) < 0) {
        printf("Insert failed!\n");
    } else {
        display_link_list(&link_list);
    }

    printf("--- Find value 5 ---\n");
    struct found_info *fd_info = find(&link_list, 5);
    if (!fd_info) {
        printf("Cannot find value 5 in link list.\n");
    } else {
        printf("Value 5 found at the following positions:\n");
        for (unsigned int i = 0; i < fd_info->found_count; i++) {
            printf("%u ", fd_info->found_index_list[i]);
        }
        printf("\n");
    }
    free(fd_info);
    fd_info = NULL;

    printf("--- Delete element at pos 2 ---\n");
    if (delete(&link_list, 2) < 0) {
        printf("Delete failed!\n");
    }else {
        display_link_list(&link_list);
    }

    // 在程序结束前释放链表内存
    free_link_list(&link_list);
    printf("--- Link list memory freed ---\n");

    return 0;
}
