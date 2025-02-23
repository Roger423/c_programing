#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

#define NAME_LEN 25

struct part {
    int number;
    char name[NAME_LEN + 1];
    int on_hand;
    struct part *next;
};

struct part *inventory = NULL;

int num_parts = 0;

struct part *find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);
void print_menu(void);

int main(void)
{
    char code;

    print_menu();

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch (code)
        {
        case 'i': insert();
            break;
        case 's': search();
            break;
        case 'u': update();
            break;
        case 'p': print();
            break;
        case 'q': return 0;
        default: printf("Illegal code\n");
        }
    }
}

void print_menu(void)
{
    printf("\n#######################################\n");
    printf("#   Enter the following key:          #\n");
    printf("#   i:  to insert a part item.        #\n");
    printf("#   s:  to search a part item.        #\n");
    printf("#   u:  to update a part item.        #\n");
    printf("#   p:  to show all part items.       #\n");
    printf("#   q:  to quit this program.         #\n");
    printf("#######################################\n\n");

}

struct part *find_part(int number)
{
    struct part *p;

    for (p = inventory; p !=NULL && number > p->number; p = p->next)
        ;
    if (p != NULL && number == p->number)
            return p;
    return NULL;
}

void insert(void)
{
    struct part *cur, *prev, *new_node;

    new_node = malloc((sizeof(struct part)));

    if (new_node == NULL) {
        printf("Databash if full; cannot add more parts.\n");
        return;
    }
    
    printf("Enter part number: ");
    scanf("%d", &new_node->number);

    for (cur = inventory, prev = NULL; cur != NULL && new_node->number > cur->number; prev = cur, cur = cur->next)
        ;
    if (cur != NULL && new_node->number == cur->number) {
        printf("Part already exists.\n");
        free(new_node);
        return;
    }

    printf("Enter part name: ");
    read_line(new_node->name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &new_node->on_hand);
    new_node->next = cur;
    if (prev == NULL)
        inventory = new_node;
    else
        prev->next = new_node;
}

void search(void)
{
    int number;
    struct part *p;

    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(number);
    if (p != NULL) {
        printf("Part name       :  %s\n", p->name);
        printf("Quantity on hand:  %d", p->on_hand);
    } else printf("Part not found!\n");
}

void update(void)
{
    int number, change;
    struct part *p;
    
    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(number);
    if (p != NULL) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        p->on_hand += change;
    } else printf("Part not found!\n");
}

void print(void)
{
    struct part *p;

    printf("------------------------------------------------\n");
    printf("Part Number    Part Name        Quantity on Hand\n\n");
    for (p = inventory; p != NULL; p = p->next)
        printf("%-11d    %-9s        %-d\n", p->number, p->name, p->on_hand);
    printf("------------------------------------------------\n");
}
