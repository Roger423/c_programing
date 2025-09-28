

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
};

struct Node* init_list()
{
    struct Node* head = (struct Node *)malloc(sizeof(struct Node));

    if (!head) {
        perror("Alloc memory for list head failed\n");
        return NULL;
    }

    head->value = 0;
    head->prev = head;
    head->next = head;

    return head;
}

bool is_empty(struct Node *list_head) {
    return list_head->next == list_head;
}

int insert_front(struct Node *list_head, int insert_value)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        perror("Alloc memory for new node failed!\n");
        return -1;
    }

    new_node->value = insert_value;

    new_node->next = list_head->next;
    new_node->prev = list_head;
    new_node->next->prev = new_node;
    list_head->next = new_node;

    return 0;
}

int insert_back(struct Node *list_head, int insert_value)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        perror("Alloc memory for new node failed!\n");
        return -1;
    } 

    new_node->value = insert_value;

    new_node->prev = list_head->prev;
    new_node->next = list_head;
    list_head->prev = new_node;
    new_node->prev->next = new_node;
    
    return 0;
}

struct Node *find_node(struct Node *list_head, int node_value)
{
    if (is_empty(list_head)) {
        printf("List is empty, cannot find the node with value: %d\n", node_value);
        return NULL;
    }

    struct Node *p = list_head->next;
    while (p != list_head) {
        if (p->value == node_value) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int delete_node(struct Node *list_head, int node_value)
{
    struct Node *del_node = find_node(list_head, node_value);
    if (!del_node) {
        printf("Cannot find a node with value %d, delete node failed!\n", node_value);
        return -1;
    }

    del_node->prev->next = del_node->next;
    del_node->next->prev = del_node->prev;

    free(del_node);

    return 0;
}

void display_forward(struct Node *list_head)
{
    struct Node *p = list_head->next;
    unsigned int idx = 0;
    printf("--------------------------------------------------------\n");
    printf("All node value of list at forward direction:\n");
    while (p != list_head) {
        printf("Node %u value of list at direction of forward: %d\n", idx, p->value);
        idx++;
        p = p->next;
    }
    printf("--------------------------------------------------------\n");
}

void display_backward(struct Node *list_head)
{
    struct Node *p = list_head->prev;
    unsigned int idx = 0;
    printf("--------------------------------------------------------\n");
    printf("All node value of list at backward direction:\n");
    while (p != list_head) {
        printf("Node %u value of list at direction of backward: %d\n", idx, p->value);
        idx++;
        p = p->prev;
    }
    printf("--------------------------------------------------------\n");
}

void free_list(struct Node *list_head)
{
    struct Node *current_node = list_head->next;
    

    while(current_node != list_head) {
        struct Node *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }

    free(list_head);
    list_head = NULL;
}

int main()
{
    const int forward_insert_list[] = {1, 2, 3};
    const int backward_insert_list[] = {4, 5, 6};
    
    struct Node *link_list_head = init_list();
    for (int i = 0; i < 3; i++) {
        if (insert_front(link_list_head, forward_insert_list[i]) != 0) {
            printf("Insert node for value %d failed!\n", forward_insert_list[i]);
        }
    }

    display_forward(link_list_head);

    for (int i = 0; i < 3; i++) {
        if (insert_back(link_list_head, backward_insert_list[i]) != 0) {
            printf("Insert node for value %d failed!\n", backward_insert_list[i]);
        }
    }

    display_backward(link_list_head);

    if (delete_node(link_list_head, 3) != 0) {
        printf("Delete node with value 3 failed!\n");
    } else {
        printf("Display all node after delete 3:\n");
        display_forward(link_list_head);
        display_backward(link_list_head);
    }

    free_list(link_list_head);

    return 0;
}
