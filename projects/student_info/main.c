#include "common.h"
#include "display.h"
#include "add.h"
#include "find.h"
#include "del.h"
#include "update.h"


int main_page(students *stus);
void print_menu(void);


int main()
{
    students all_stus;
    all_stus.student_list = (student_info *)malloc(INIT_STU_CNT * sizeof(student_info));
    if (all_stus.student_list == NULL) {
        fprintf(stderr, "Failed to allocate initial memory!\n");
        return 1;
    }
    all_stus.max_stu_num = INIT_STU_CNT;
    all_stus.stu_num = 0;
    all_stus.last_stu_id = 0;

    return main_page(&all_stus);
}

void print_menu(void)
{
    printf("%s\n", MENU_SPLIT_LINE);
    printf("**  Student Management System  **\n");
    printf("%s\n", MENU_SPLIT_LINE);
    printf("S: Show all students info\n");
    printf("A: Add students info\n");
    printf("D: Delete students info\n");
    printf("U: Update students info\n");
    printf("F: Find students info\n");
    printf("E: Exit\n");
    printf("%s\n", MENU_SPLIT_LINE);
    printf("Please input your choice:");
    
}

int main_page(students *stus)
{
    while(true)
    {
        print_menu();

        char choice_line[16];

        if (get_input_line(choice_line, sizeof(choice_line), stdin) == EOF) {
            printf("\nInput error or EOF detected, exiting...\n");
            free(stus->student_list);
            stus->student_list = NULL;
            return 0;
        }
        char choice = toupper(choice_line[0]);

        switch (choice)
        {
        case 'S':
            printf("Showing all students info...\n");
            show_all_students_info(stus);
            break;

        case 'A':
            printf("Adding student info...\n");
            add_students_info(stus);
            break;

        case 'D':
            printf("Deleting student info...\n");
            delete_student_info(stus);
            break;

        case 'U':
            printf("Updating student info...\n");
            update_student_info(stus);
            break;

        case 'F':
            printf("Finding student info...\n");
            find_student_info(stus);
            break;

        case 'E':
            free(stus->student_list);
            stus->student_list = NULL;
            return 0;

        default:
            printf("\n%s\n", SPLIT_LINE);
            printf("Your input is %c.\n", choice);
            printf("Invalid input, please input a valid character\n");
        }
    }
}
