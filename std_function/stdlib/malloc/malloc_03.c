//Struct Allocation
//For structs, malloc is often used:

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Data;

int main() {
    Data *d = (Data *)malloc(sizeof(Data));
    if (d == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    d->id = 1;
    d->value = 3.14;
    printf("ID: %d, Value: %.2f\n", d->id, d->value);

    free(d);
    return 0;
}

