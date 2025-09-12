#include "find.h"


found_info* find_student_info_by_id(students *stus, char *stu_id)
{
    found_info *fd_info = (found_info *)malloc(FOUND_INFO_SIZE(1));
    if (fd_info == NULL) {
        fprintf(stderr, "Failed to allocate memory for found_info.\n");
        return NULL;
    }

    printf("Find student info by student ID. Only one student is to be found.\n");
    int found_idx = -1;
    for (int i = 0; i < stus->stu_num; i++) {
        if (strcmp(stus->student_list[i].id, stu_id) == 0) {
            found_idx = i;
            break;
        }
    }
    fd_info->found_count = found_idx >= 0 ? 1 : 0;
    fd_info->found_index[0] = found_idx;

    return fd_info;
}

found_info* find_student_info_by_phone_num(students *stus, char *phone_num)
{
    found_info *fd_info = (found_info *)malloc(FOUND_INFO_SIZE(1));
    if (fd_info == NULL) {
        fprintf(stderr, "Failed to allocate memory for found_info.\n");
        return NULL;
    }

    printf("Find student info by student phone number. Only one student is to be found.\n");
    int found_idx = -1;
    for (int i = 0; i < stus->stu_num; i++) {
        if (strcmp(stus->student_list[i].phone_num, phone_num) == 0) {
            found_idx = i;
            break;
        }
    }
    fd_info->found_count = (found_idx >= 0) ? 1 : 0;
    fd_info->found_index[0] = found_idx;

    return fd_info;
}

found_info* find_student_info_by_name(students *stus, char *stu_name)
{
    printf("Find student info by student name. May be multiple students to be found.\n");
    int found_count = 0;

    int *found_indices = (int*)malloc(sizeof(int) * stus->stu_num);
    if (found_indices == NULL) {
        fprintf(stderr, "Failed to allocate memory for temporary indices.\n");
        return NULL;
    }

    for (int i = 0; i < stus->stu_num; i++) {
        if (strcmp(stus->student_list[i].name, stu_name) == 0) {
            found_indices[found_count++] = i;
        }
    }

    found_info *fd_info = (found_info *)malloc(FOUND_INFO_SIZE(found_count));
    if (fd_info == NULL) {
        fprintf(stderr, "Failed to allocate memory for found_info.\n");
        free(found_indices);
        return NULL;
    }

    fd_info->found_count = found_count;
    if (found_count > 0) {
        memcpy(fd_info->found_index, found_indices, sizeof(int) * found_count);
    }
    free(found_indices);
    return fd_info;
}

int find_student_info(students *stus)
{
    if (stus->stu_num == 0){
        printf("No student info exist!\n");
        return -1;
    }
    found_info *fd_info = NULL;
    printf("Find student information records.\n\nPlease select which information you need to search by:\n");
    printf("Student ID(I) | Student Name(N) | Phone Number(P) : ");

    char choice_line[4];
    get_input_line(choice_line, sizeof(choice_line), stdin);
    char find_choice = toupper(choice_line[0]);

    switch (find_choice)
    {
    case 'I':
        printf("Please input student ID:");
        char stu_id[8];
        get_input_line(stu_id, sizeof(stu_id), stdin);
        fd_info = find_student_info_by_id(stus, stu_id);
        break;
    case 'N':
        printf("Please input student name:");
        char stu_name[MAX_NAME_LEN];
        get_input_line(stu_name, sizeof(stu_name), stdin);
        fd_info = find_student_info_by_name(stus, stu_name);
        break;
    case 'P':
        printf("Please input student phone number:");
        char stu_phone_num[MAX_PHONE_LEN];
        get_input_line(stu_phone_num, sizeof(stu_phone_num), stdin);
        fd_info = find_student_info_by_phone_num(stus, stu_phone_num);
        break;
    default:
        printf("Invalid choice, please press 'I' or 'N' or 'P'\n");
        break;
    }

    if (fd_info == NULL) {
        fprintf(stderr, "No search was performed due to invalid input or OOM.\n");
        return -1;
    }

    if (fd_info->found_count > 0) {
        printf("%s\n", SPLIT_LINE);
        printf("Find %d students information:\n\n", fd_info->found_count);

        for (int i = 0; i < fd_info->found_count; i++) {
            print_student_info(&stus->student_list[fd_info->found_index[i]]);
            printf("%s\n", SPLIT_LINE);
        }
        
        free(fd_info);
        return 0;
    }
    else {
        printf("Find no students information\n");
        free(fd_info);
        return -1;
    }
}
