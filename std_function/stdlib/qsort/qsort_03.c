
//(3) 排序结构体数组（按字段）

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
} Person;

int cmp_person(const void *a, const void *b) {
    const Person *pa = (const Person *)a;
    const Person *pb = (const Person *)b;
    // 按年龄升序
    return pa->age - pb->age;
}

int main() {
    Person people[] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 28}
    };
    int n = sizeof(people) / sizeof(people[0]);

    qsort(people, n, sizeof(Person), cmp_person);

    printf("排序结果:\n");
    for (int i = 0; i < n; i++) {
        printf("%s (%d)\n", people[i].name, people[i].age);
    }
    return 0;
}
