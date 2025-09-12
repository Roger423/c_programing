
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define INIT_STU_CNT 10
#define STU_CNT_INCREMENT 5
#define STU_ID_LEN 6
#define MAX_STU_ID 9999

#define MAX_NAME_LEN 64
#define MAX_GENDER_LEN 8
#define MAX_PHONE_LEN 16
#define MAX_ADDRESS_LEN 256

#define SPLIT_LINE "----------------------------------------------------------"
#define MENU_SPLIT_LINE "-----------------------------------"


typedef struct  
{
    char id[STU_ID_LEN];
    char name[MAX_NAME_LEN];
    char gender[MAX_GENDER_LEN];
    unsigned short age;
    char phone_num[MAX_PHONE_LEN];
    char address[MAX_ADDRESS_LEN];
} student_info;

typedef struct
{
    student_info *student_list;
    int stu_num;
    int max_stu_num;
    unsigned int last_stu_id;
} students;

int get_input_line(char *dst, size_t size, FILE *stream);

#endif
