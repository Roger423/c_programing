
#ifndef FIND_H
#define FIND_H

#include "common.h"
#include "display.h"


typedef struct
{
    int found_count;
    int found_index[];
} found_info;

#define FOUND_INFO_SIZE(n) (sizeof(found_info) + sizeof(int) * (n))


found_info* find_student_info_by_id(students *stus, char *stu_id);
found_info* find_student_info_by_phone_num(students *stus, char *phone_num);
found_info* find_student_info_by_name(students *stus, char *stu_name);
int find_student_info(students *stus);

#endif
