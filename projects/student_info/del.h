#ifndef DEL_H
#define DEL_H

#include "common.h"
#include "find.h"
#include "display.h"


int delete_student_by_id(students *stus, char *stu_id);
int delete_student_by_name(students *stus, char *stu_name);
int delete_student_info(students *stus);

#endif
