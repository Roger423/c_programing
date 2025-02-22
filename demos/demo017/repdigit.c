#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        printf("n --> %ld\n", n);
        digit = n % 10;
        printf("digit --> %d\n", digit);
        if (digit_seen[digit])
            break;
        digit_seen[digit] = true;
        n /= 10;
    }

    if (n > 0)
        printf("Repeated digit\n");
    else
        printf("No repeated digit\n");
    
    return 0;
}
