
#include "update.h"


static bool check_update_finished()
{
    printf("Is update student information finished?(Y/N):");
    char finished_choice_str[4];
    get_input_line(finished_choice_str, sizeof(finished_choice_str), stdin);
    char finished_choice = toupper(finished_choice_str[0]);
    return (finished_choice == 'Y') ? true : false;
}

static bool update_student_name(students *stus, int stu_idx)
{
    printf("Please input student name:");
    char stu_name[MAX_NAME_LEN];
    get_input_line(stu_name, sizeof(stu_name), stdin);
    unsigned int name_len = strlen(stu_name);
    if (name_len > 0) {
        strncpy(stus->student_list[stu_idx].name, stu_name, MAX_NAME_LEN - 1);
        stus->student_list[stu_idx].name[MAX_NAME_LEN - 1] = '\0';
    }
    return check_update_finished();
}

static bool update_student_gender(students *stus, int stu_idx)
{
    printf("Please input student gender(F/M):");
    char gender_str[4];
    get_input_line(gender_str, sizeof(gender_str), stdin);
    char gender_choice = toupper(gender_str[0]);
    switch (gender_choice)
    {
    case 'F':
        strncpy(stus->student_list[stu_idx].gender, "Female", MAX_GENDER_LEN - 1);
        break;
    case 'M':
        strncpy(stus->student_list[stu_idx].gender, "Male", MAX_GENDER_LEN - 1);
        break;
    default:
        printf("Invalid gender input, set to 'Unknown'\n");
        // strncpy(stus->student_list[stu_idx].gender, "Unknown", MAX_GENDER_LEN - 1);
        snprintf(stus->student_list[stu_idx].gender, sizeof(stus->student_list[stu_idx].gender), "Unknown");
        break;
    }
    // stus->student_list[stu_idx].gender[MAX_GENDER_LEN - 1] = '\0';
    return check_update_finished();
}

static bool update_student_age(students *stus, int stu_idx)
{
    printf("Please input student age:");
    char age_str[16];
    get_input_line(age_str, sizeof(age_str), stdin);
    unsigned long new_age = strtoul(age_str, NULL, 10);
    if (new_age == 0 || new_age >= 200) {
        printf("Invalid age, keep unchanged.\n");
    }
    else {
        stus->student_list[stu_idx].age = (unsigned short)new_age;
    }
    
    return check_update_finished();
}

static bool update_student_phone_num(students *stus, int stu_idx)
{
    printf("Please input student phone number:");
    char phone_num_str[MAX_PHONE_LEN];
    get_input_line(phone_num_str, sizeof(phone_num_str), stdin);
    strncpy(stus->student_list[stu_idx].phone_num, phone_num_str, MAX_PHONE_LEN - 1);
    stus->student_list[stu_idx].phone_num[MAX_PHONE_LEN - 1] = '\0';
    return check_update_finished();
}

static bool update_student_addr(students *stus, int stu_idx)
{
    printf("Please input student address:");
    char addr_str[MAX_ADDRESS_LEN];
    get_input_line(addr_str, sizeof(addr_str), stdin);
    strncpy(stus->student_list[stu_idx].address, addr_str, MAX_ADDRESS_LEN - 1);
    stus->student_list[stu_idx].address[MAX_ADDRESS_LEN - 1] = '\0';
    return check_update_finished();
}

static int update_student_info_items(students *stus, int stu_idx)
{
    while (true)
    {
        printf("Which student information item you want to update.\n");
        printf("Press the number in the parentheses following the information item.\n");
        printf("Name(1) | Gender(2) | Age(3) | Phone number(4) | Address(5) :");
        char update_choice_str[4];
        get_input_line(update_choice_str, sizeof(update_choice_str), stdin);
        unsigned short update_choice = (unsigned short)strtoul(update_choice_str, NULL, 10);

        switch (update_choice)
        {
        case 1:
            if (update_student_name(stus, stu_idx)) return 0;
            break;
        case 2:
            if (update_student_gender(stus, stu_idx)) return 0;
            break;
        case 3:
            if (update_student_age(stus, stu_idx)) return 0;
            break;
        case 4:
            if (update_student_phone_num(stus, stu_idx)) return 0;
            break;
        case 5:
            if (update_student_addr(stus, stu_idx)) return 0;
            break;
        default:
            printf("Invalid input!\n");
            break;
        }
    }
}

static int update_student_info_by_id(students *stus, char *stu_id)
{
    found_info *fd_stu = find_student_info_by_id(stus, stu_id);
    if (fd_stu == NULL) {
        fprintf(stderr, "OOM when searching by ID.\n");
        return -1;
    }
    if (fd_stu->found_count == 0) {
        printf("Cannot find a student information with ID %s\n", stu_id);
        free(fd_stu);
        return -1;
    }

    printf("Student information with ID %s as follows:\n", stu_id);
    printf("%s\n", SPLIT_LINE);
    print_student_info(&(stus->student_list[fd_stu->found_index[0]]));
    printf("%s\n", SPLIT_LINE);
    
    printf("Are you want to update information of this student(Y/N):");
    char confirm_str[4];
    get_input_line(confirm_str, sizeof(confirm_str), stdin);
    char confirm_choice = toupper(confirm_str[0]);

    int ret = 0;
    if (confirm_choice == 'Y') {
        ret = update_student_info_items(stus, fd_stu->found_index[0]);
    }

    free(fd_stu);
    return ret;
}

static int update_student_info_by_name(students *stus, char *stu_name)
{
    found_info *fd_stu = find_student_info_by_name(stus, stu_name);
    if (fd_stu == NULL) {
        fprintf(stderr, "OOM when searching by name.\n");
        return -1;
    }
    if (fd_stu->found_count == 0) {
        printf("Cannot find a student information with name %s\n", stu_name);
        free(fd_stu);
        return -1;
    }

    printf("Student information with name %s are as follows:\n", stu_name);
    for (int i = 0; i < fd_stu->found_count; i++) {
        printf("%s\n", SPLIT_LINE);
        print_student_info(&(stus->student_list[fd_stu->found_index[i]]));
    }
    printf("%s\n", SPLIT_LINE);
    
    printf("Which student information are you want to update?\n");
    printf("Please input the ID of the student:");
    char stu_id[16];
    get_input_line(stu_id, sizeof(stu_id), stdin);
    int ret = update_student_info_by_id(stus, stu_id);

    free(fd_stu);
    return ret;
}

int update_student_info(students *stus)
{
    printf("Update student information records.\n");
    printf("To find the student infomation.\nPlease select which information you need to find by:\n");
    printf("Student ID(I) | Student Name(N): ");
    char find_choice_str[4];
    get_input_line(find_choice_str, sizeof(find_choice_str), stdin);

    char find_choice = toupper(find_choice_str[0]);

    switch (find_choice)
    {
    case 'I':
        printf("Please input student ID:");
        char stu_id[16];
        get_input_line(stu_id, sizeof(stu_id), stdin);
        return update_student_info_by_id(stus, stu_id);
    case 'N':
        printf("Please input student name:");
        char stu_name[MAX_NAME_LEN];
        get_input_line(stu_name, sizeof(stu_name), stdin);
        return update_student_info_by_name(stus, stu_name);
    default:
        printf("Invalid input!\n");
        return -1;
    }
}
