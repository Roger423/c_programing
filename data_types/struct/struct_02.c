/*
Accessing Members of a Struct using Pointers

When you work with structures via pointers, you access members using the -> operator instead of the . operator.
*/

#include <stdio.h>

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person *personPtr;
    struct Person person1 = {"Bob", 25, 5.8};

    personPtr = &person1;

    // Accessing struct members using a pointer
    printf("Name: %s\n", personPtr->name);
    printf("Age: %d\n", personPtr->age);
    printf("Height: %.2f\n", personPtr->height);

    return 0;
}
