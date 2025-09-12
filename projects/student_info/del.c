#include "del.h"


int delete_student_by_id(students *stus, char *stu_id)
{
    printf("Delete student info by student ID: %s\n", stu_id);
    found_info *fd_stu = find_student_info_by_id(stus, stu_id);

    if (fd_stu == NULL) {
        fprintf(stderr, "OOM when searching by ID.\n");
        return -1;
    }

    if (fd_stu->found_count == 0) {
        printf("Cannot find the student infomation with ID: %s\n", stu_id);
        free(fd_stu);
        return -1;
    }
    int del_idx = fd_stu->found_index[0];
    printf("Are you sure the following student info is to be deleted!\n");
    printf("%s\n", SPLIT_LINE);
    print_student_info(&(stus->student_list[del_idx]));
    printf("%s\n", SPLIT_LINE);
    printf("Press 'Y' to confirm. Press 'N' to cancle:");
    char del_choice_str[4];
    get_input_line(del_choice_str, sizeof(del_choice_str), stdin);
    char del_choice = toupper(del_choice_str[0]);
    if (del_choice == 'Y') {
        int ele_to_move = stus->stu_num - del_idx - 1;
        if (ele_to_move > 0) {
            memmove(&stus->student_list[del_idx], &stus->student_list[del_idx + 1], ele_to_move * sizeof(student_info));
        }
        stus->stu_num--;
        printf("Student information with ID %s deleted.\n", stu_id);
    }
    free(fd_stu);

    return 0;
}

int delete_student_by_name(students *stus, char *stu_name)
{
    printf("Delete student info by student name: %s\n", stu_name);
    found_info *fd_stu = find_student_info_by_name(stus, stu_name);

    if (fd_stu == NULL) {
        fprintf(stderr, "OOM when searching by name.\n");
        return -1;
    }

    if (fd_stu->found_count == 0) {
        printf("Cannot find the student infomation with name: %s\n", stu_name);
        free(fd_stu);
        return -1;
    }

    printf("Students infomation with name %s are as follows:\n", stu_name);
    for (int i = 0; i < fd_stu->found_count; i++) {
        printf("%s\n", SPLIT_LINE);
        print_student_info(&(stus->student_list[fd_stu->found_index[i]]));
    }
    printf("%s\n", SPLIT_LINE);
    printf("Which student you want to delete, please input student ID:");
    char stu_id[STU_ID_LEN];
    get_input_line(stu_id, sizeof(stu_id), stdin);

    bool check_id = false;
    for (int i = 0; i < fd_stu->found_count; i++) {
        if (strcmp(stus->student_list[fd_stu->found_index[i]].id, stu_id) == 0) {
                check_id = true;
                break;
            }
    }
    int del_res = -1;
    if (check_id) {
        del_res = delete_student_by_id(stus, stu_id);
    }
    else {
        printf("The student ID you just input not match any of the found student information with name %s\n", stu_name);
        printf("Delete failed\n");
    }
    
    free(fd_stu);

    return del_res < 0 ? -1 : 0;
}

int delete_student_info(students *stus)
{
    printf("Delete student information records.\n\nPlease select which information you need to delete by:\n");
    printf("Student ID(I) | Student Name(N): ");
    char del_choice_str[4];
    get_input_line(del_choice_str, sizeof(del_choice_str), stdin);
    char del_choice = toupper(del_choice_str[0]);
    switch (del_choice)
    {
    case 'I':
        printf("Please input student ID:");
        char stu_id[STU_ID_LEN];
        get_input_line(stu_id, sizeof(stu_id), stdin);
        return delete_student_by_id(stus, stu_id);
    case 'N':
        printf("Please input student Name:");
        char stu_name[MAX_NAME_LEN];
        get_input_line(stu_name, sizeof(stu_name), stdin);
        return delete_student_by_name(stus, stu_name);
    default:
        printf("Invalid delete choice!\n");
        return -1;
        break;
    }
}
