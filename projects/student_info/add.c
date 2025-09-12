#include "add.h"


int extend_students_info_list(students *stus)
{
    int new_max_num = stus->max_stu_num + STU_CNT_INCREMENT;
    size_t new_size = (size_t)new_max_num * sizeof(student_info);
    student_info *new_list = (student_info *)realloc(stus->student_list, new_size);
    if (!new_list) {
        fprintf(stderr, "realloc failed during extend student info list\n");
        return -1;
    }
    stus->student_list = new_list;
    stus->max_stu_num = new_max_num;
    return 0;
}

int add_students_info(students *stus)
{
    if (stus->stu_num == stus->max_stu_num) {
        if (extend_students_info_list(stus) != 0) return -1;
    }
    
    stus->last_stu_id++;
    if (stus->last_stu_id > MAX_STU_ID){
        fprintf(stderr, "Student number exceed the max number %d\n", MAX_STU_ID);
        stus->last_stu_id--;
        return -1;
    }

    student_info *new_stu = &stus->student_list[stus->stu_num];

    snprintf(new_stu->id, sizeof(new_stu->id), "%04u", stus->last_stu_id);

    printf("Add information for a new student.\n\nPlease input student name:");

    get_input_line(new_stu->name, sizeof(new_stu->name), stdin);

    while (true) {
        printf("Please input student age(0 < age < 200):");

        char age_str[8];
        get_input_line(age_str, sizeof(age_str), stdin);

        unsigned short age = (unsigned short)strtoul(age_str, NULL, 10);
        if (age <= 0 || age >= 200) {
            printf("Invalid age input. Please try again.\n");
        }
        else {
            new_stu->age = age;
            break;
        }
    }

    printf("Please input student gender(F/M):");
    char gender_choice_line[4];

    get_input_line(gender_choice_line, sizeof(gender_choice_line), stdin);
    char gender_choice = toupper(gender_choice_line[0]);
    switch (gender_choice)
    {
    case 'F':
        strncpy(new_stu->gender, "Female", sizeof(new_stu->gender) - 1);
        break;
    case 'M':
        strncpy(new_stu->gender, "Male", sizeof(new_stu->gender) - 1);
        break;
    default:
        printf("Invalid gender input, set to 'Unknown'\n");
        // strncpy(new_stu->gender, "Unknown", sizeof(new_stu->gender) - 1);
        snprintf(new_stu->gender, sizeof(new_stu->gender), "Unknown");
        break;
    }
    // new_stu->gender[sizeof(new_stu->gender) - 1] = '\0';

    printf("Please input student phone number:");
    get_input_line(new_stu->phone_num, sizeof(new_stu->phone_num), stdin);

    printf("Please input student address:");
    get_input_line(new_stu->address, sizeof(new_stu->address), stdin);

    stus->stu_num++;
    printf("Student added successful!\n");
    return 0;
}
