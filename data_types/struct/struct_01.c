/*
A struct (short for "structure") in C is a user-defined data type that allows grouping different data types under a 
single name. It is one of the most commonly used features in C for creating complex data models. struct enables 
grouping of variables of different types into a single unit, and each variable within a struct is called a member 
or field.

Syntax:

struct structure_name {
    data_type member1;
    data_type member2;
    ...
};

structure_name: The name of the structure.
member1, member2, ...: The members or fields of the structure, each having its own data type (it can be any valid 
                       C type, including arrays, other structs, pointers, etc.).
*/

//Example: Basic Structure

#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person person1;

    // Assign values to the members of the structure
    strcpy(person1.name, "Alice");
    person1.age = 30;
    person1.height = 5.5;

    // Displaying the structure members
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %.2f\n", person1.height);

    return 0;
}

/*
Key Points:
Defining a struct: A struct is defined using the struct keyword followed by the structure name, and inside the curly 
braces {} we define the members (fields) of the structure.

Accessing Members: The members of a structure can be accessed using the dot (.) operator.


struct Person person1;
person1.age = 30;

Initialization: A structure variable can be initialized at the time of declaration, using the following syntax:


struct Person person1 = {"Alice", 30, 5.5};

Memory Layout: A struct occupies memory that is the sum of the memory required by its members. However, 
the actual memory layout might have padding between the members to ensure proper alignment.
*/